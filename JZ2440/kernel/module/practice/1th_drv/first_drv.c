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

// add sys info
static struct class *firstdrv_class;
static struct class_device *firstdrv_class_dev;
int major;
volatile unsigned long *gpfcon = NULL;
volatile unsigned long *gpfdat = NULL;

static int first_drv_open(struct inode *inode,struct file *file)
{
	printk("first_drv_open\n");
	/*	config GPF4,5,6 as output */
	*gpfcon &= ~((0x3 << (4*2)) | (0x3 << (5*2)) | (0x3 << (6*2)) );
	*gpfcon |= ((0x01 << (4*2)) | (0x01 << (5*2)) | (0x01 << (6*2)));
	return 0;
}
static int first_drv_write(struct file *file,const char __user *buf,size_t count,loff_t *ppos)
{
	int val;

	copy_from_user(&val,buf,count);
	
	printk("first_drv_write\n");

	if(val != 1)
	{
		*gpfdat |= ((1<<4)|(1<<5)|(1<<6));
	}
	else
	{
		*gpfdat &= ~((1<<4)|(1<<5)|(1<<6));
	}
	return 0;
}
static struct file_operations first_drv_fops={
	.owner = THIS_MODULE,
	.open = first_drv_open,
	.write = first_drv_write,
};
int first_drv_init(void)
{
	major = register_chrdev(major,"first_drv",&first_drv_fops);
	firstdrv_class = class_create(THIS_MODULE,"firstdrv");
	if(IS_ERR(firstdrv_class))
		return PTR_ERR(firstdrv_class);

	firstdrv_class_dev = class_device_create(firstdrv_class,NULL,MKDEV(major,0),NULL,"xyz");
	if(unlikely(IS_ERR(firstdrv_class_dev)))
		return PTR_ERR(firstdrv_class_dev);

	gpfcon = (volatile unsigned long *)ioremap(0x56000050,16);
	gpfdat = (gpfcon + 1);
	
	return 0;
}
void first_drv_exit(void)
{
	unregister_chrdev(111,"first_drv");
	class_device_unregister(firstdrv_class_dev);
	class_destroy(firstdrv_class);
	iounmap(gpfcon);
}

module_init(first_drv_init);
module_exit(first_drv_exit);

MODULE_LICENSE("GPL");
