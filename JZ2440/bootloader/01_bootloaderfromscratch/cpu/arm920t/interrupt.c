/*
 * irq - irq code for ARM 2440
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
 *   01/15/2015 Eric: initialization creation
 *
 */

#include<asm/arch_s3c24x0/hardware.h>
#include"uart.h"

void (*isr_handle_array[50])(void);

void Dummy_isr(void)
{

}
void irq_init(void)
{
    int i = 0;
#if 0
    for(i = 0;i < sizeof(isr_handle_array) / sizeof(isr_handle_array[0]);i++){
        isr_handle_array[i] = Dummy_isr;
    }
#endif

    INTMOD = 0x0;       // set all interrupts as IRQ mode
    INTMSK = 0xffffffff;// mask all interrupts

}
void Interrupt_handler(void)
{
    unsigned long oft = INTOFFSET;

    switch(oft)
    {
        case 28:
            uart_irq();
            SRCPND = 1 << oft;
            INTPND = 1 << oft;
            break;
        default:
            break;
    }

    SRCPND |= ~( 1 << oft);
}
