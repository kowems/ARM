#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/init.h>
#include<linux/delay.h>
#include<asm/uaccess.h>
#include<asm/irq.h>
#include<asm/io.h>
#include<asm/arch/regs-gpio.h>
#include<asm/hardware.h>

int major;
static struct class *btn_poll_drv_class;
static struct class_device *btn_poll_drv_class_device;

volatile unsigned long *gpfcon;
volatile unsigned long *gpfdat;

volatile unsigned long *gpgcon;
volatile unsigned long *gpgdat;

static int btn_poll_drv_open(struct inode *inod,struct file *file)
{
	/* set GPF0,2 as input */
	*gpfcon &= ~((0x3 << (0*2))|(0x3 << (2*2)));
	/* set GPG3,11 as input */
	*gpgcon &= ~((0x3 << (3*2))|(0x3 << (11*2)));
	
	return 0;
}

ssize_t btn_poll_drv_read(struct file *file,char __user *buf,size_t size,loff_t *ppos)
{
	unsigned char key_vals[4];
	int regval;

	if(size != sizeof(key_vals))
		return -EINVAL;
	
	/* read GPF0,2 */
	regval = *gpfdat;
	key_vals[0] = (regval & (1 << 0)) ? 1:0;
	key_vals[1] = (regval & (1 << 2)) ? 1:0;

	/* read GPG3,11 */
	key_vals[2] = (regval & (1 << 3)) ? 1:0;
	key_vals[3] = (regval & (1 << 11)) ? 1:0;

	copy_to_user(buf,key_vals,sizeof(key_vals));
	
	return sizeof(key_vals);
}

static struct file_operations btn_poll_drv_fops = {
	.owner = THIS_MODULE,
	.open  = btn_poll_drv_open,
	.read  = btn_poll_drv_read,
};

static int btn_poll_drv_init(void)
{
	major = register_chrdev(0,"btn_poll_drv",&btn_poll_drv_fops);

	btn_poll_drv_class = (struct class *)class_create(THIS_MODULE,"firstdrv");
	if(IS_ERR(btn_poll_drv_class))
		return PTR_ERR(btn_poll_drv_class);

	btn_poll_drv_class_device = (struct class_device *)class_device_create(btn_poll_drv_class,NULL,MKDEV(major,0),NULL,"btn_poll");
	if(unlikely(IS_ERR(btn_poll_drv_class_device)))
		return PTR_ERR(btn_poll_drv_class_device);

	gpfcon = (volatile unsigned long *)ioremap(0x56000050,16);
	gpfdat = gpfcon + 1;

	gpgcon = (volatile unsigned long *)ioremap(0x56000060,16);
	gpgdat = gpgcon + 1;

	return 0;
}

static int btn_poll_drv_exit(void)
{
	unregister_chrdev(major,"btn_poll_drv");

	class_device_unregister(btn_poll_drv_class_device);
	class_destroy(btn_poll_drv_class);

	iounmap(gpfcon);
	iounmap(gpgcon);

	return 0;
}

module_init(btn_poll_drv_init);
module_exit(btn_poll_drv_exit);

MODULE_LICENSE("GPL");
