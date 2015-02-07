#include "s3c2440.h"

void EINT_handle()
{
    unsigned long oft = INTOFFSET;
    unsigned long val = 0;

    switch(oft)
    {
        case 0:
            GPFDAT |= (0x7 << 4);   // turn off all leds
            GPFDAT &= ~(1 << 4);    // turn on led1
            break;
        case 2:
            GPFDAT |= (0x7 << 4);    // turn off all leds
            GPFDAT &= ~(1 << 5);     // turn on led2
            break;
        case 5:
            GPFDAT |= (0x7 << 4);   // turn off all leds
            GPFDAT &= ~(1 << 6);    // turn on led4
            break;
        default:
            break;
    }
    // clear interrupt
    EINTPEND = (1 << 11);
    SRCPND = 1 << oft;
    INTPND = 1 << oft;
}
