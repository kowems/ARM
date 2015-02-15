#include<nand.h>
#include<uart.h>
#include<stdio.h>
#include<asm/setup.h>
#include<asm/mach-types.h>

extern void do_bootm_linux(void);

#define BOOT_DEBUG 1
#ifdef BOOT_DEBUG
#include<asm/arch_s3c24x0/hardware.h>
void led2_on(void)
{
    GPFCON = 0x00000100;
    GPFDAT = 0x00000000;
}
#endif

void start_boot(void)
{
    void (*the_kernel)(int zero,int arch,unsigned int params);

    /* init serial */
    uart_init();

    //puts("aaaaaaa\n");
    printf("test........................\n\r");
    /* read kernel from nand to sdram */
    nand_read((unsigned char *)0x30008000,0x60000 + 64,0x200000);
    /* set booting parameters */
    do_bootm_linux();
    led2_on();
    /* jump to kernel */
    the_kernel = (void (*)(int,int,unsigned int))0x30008000;
    the_kernel(0,MACH_TYPE_S3C2440,0x30000100);
}
