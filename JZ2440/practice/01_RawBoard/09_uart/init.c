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
