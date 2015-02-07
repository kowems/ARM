/*****************************************************************
 *
 * File: init.c
 * Function: initialze necessary hardware
 *
 *****************************************************************/

#include"s3c2440.h"

#define GPF4_out    (1 << (4*2))
#define GPF5_out    (1 << (5*2))
#define GPF6_out    (1 << (6*2))

#define GPF4_msk    (3 << (4*2))
#define GPF5_msk    (3 << (5*2))
#define GPF6_msk    (3 << (6*2))

#define GPF0_eint   (0x2 << (0*2))
#define GPF2_eint   (0x2 << (2*2))
#define GPG3_eint   (0x2 << (3*2))

#define GPF0_msk    (3 << (0*2))
#define GPF2_msk    (3 << (2*2))
#define GPG3_msk    (3 << (3*2))
/*
 * disable watchdog
 */
void disable_watch_dog(void)
{
    WTCON = 0; // write 0 to WTCON register
}

void led_init(void)
{
    GPFCON &= ~(GPF4_msk | GPF5_msk | GPF6_msk);
    GPFCON |= GPF4_out | GPF5_out | GPF6_out;
}

void key_init(void)
{
    GPFCON &= ~(GPF0_msk | GPF2_msk);
    GPFCON |= (GPF0_eint | GPF2_eint);

    GPGCON &= ~(GPG3_msk);
    GPGCON |= GPG3_eint;
}

void irq_init(void)
{
    EINTMASK &= ~(1 << 11);

    // priority
    PRIORITY = (PRIORITY & ((~0x01) | (0x3 << 7))) | (0x0 << 7);

    // enable EINT0,EINT2,EINT8_23
    INTMSK &= (~(1 << 0)) & (~(1 << 2)) & (~(1 << 5));
}
