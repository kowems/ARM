/*
 * boot linux - boot linux code for ARM 2440
 *
 * Copyright (c) 2015 Eric Ju <Eric.X.Ju@gmail.com>
 * 
 * This program is free software;you can registribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation;Either version 2 of
 * the License,or (at your option) any later version.
 *
 */

/*                  History
 *
 *   02/14/2015 Eric: initialization creation
 *
 */

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
	volatile unsigned int *p = (volatile unsigned int *)(0x30008000 + 0x800);
    void (*the_kernel)(int zero,int arch,unsigned int params);

    /* init serial */
    uart_init();

    printf("\n\rcopy kernel\n\r");
    /* read kernel from nand to sdram */
    nand_read((unsigned char *)0x30008000,0x60000+0x40,0x200000);

    printf("\n\r");
	puthex(*p);
    printf("\n\r");

    printf("set booting parameters\n\r");
    /* set booting parameters */
    do_bootm_linux();

    printf("starting kernel\n\r");
    /* jump to kernel */
    the_kernel = (void (*)(int,int,unsigned int))0x30008000;
    the_kernel(0,MACH_TYPE_S3C2440,0x30000100);
    led2_on();
}
