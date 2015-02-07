#include"s3c2440.h"
#include"uart.h"

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
