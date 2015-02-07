/******************************************************
 *
 * File: init.c
 * Function: hardware initialize function
 *
 *****************************************************/
#include "s3c2440.h"
#include "led.h"
#define S3C2440_MPLL_400MHZ     ((0x5c << 12) | (0x01 << 4) | (0x01)) // issue : ((0x5c << 12) | (0x01 << 4) | (0x01 << 1))

void disable_watch_dog(void)
{
    WTCON = 0;
}

void clock_init(void)
{
    //LOCKTIME = 0xffffffff;
    CLKDIVN = 0x5;

__asm__(
        "mrc p15,0,r1,c1,c0,0\n"
        "orr r1,r1,#0xc0000000\n"
        "mcr p15,0,r1,c1,c0,0\n"
       );

    MPLLCON = S3C2440_MPLL_400MHZ;
}

void mem_setup(void)
{
    volatile unsigned long *p = (volatile unsigned long *)MEM_CTL_BASE;

    p[0] = 0x22011110;
    p[1] = 0x00000700;  // BANKCON0
    p[2] = 0x00000700;  // BANKCON1
    p[3] = 0x00000700;  // BANKCON2
    p[4] = 0x00000700;  // BANKCON3
    p[5] = 0x00000700;  // BANKCON4
    p[6] = 0x00000700;  // BANKCON5
    p[7] = 0x00018005;  // BANKCON6
    p[8] = 0x00018005;  // BANKCON7
    /* REFRESH
     * HCLK=12MHz: 0x008c07a3
     * HCLK=100MHz: 0x008c04f4
     */
    p[9] = 0x008c04f4;  // REFRESH
    p[10] = 0x000000B1; // BANKSIZE
    p[11] = 0x00000030; // MRSRB6
    p[12] = 0x00000030; // MRSRB7
}

void copy_steppingstone_to_sdram(void)
{
    unsigned int *src = (unsigned int *)0;
    unsigned int *dest = (unsigned int *)0x30000000;

    while(src < (unsigned int *)4096){
        *dest = *src;
        src++;
        dest++;
    }
}

void clean_bss(void)
{
    extern int __bss_start,__bss_end;
    int *p = &__bss_start;

    for(;p < &__bss_end;p++)
    {
        *p = 0;
    }
}
