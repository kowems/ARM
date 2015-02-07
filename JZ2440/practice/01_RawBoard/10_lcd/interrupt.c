#include"s3c2440.h"
#include"uart.h"

void (*isr_handle_array[50])(void);

void Dummy_isr(void)
{

}

void irq_init(void)
{
    int i = 0;

    for(i = 0;i < sizeof(isr_handle_array) / sizeof(isr_handle_array[0]);i++){
        isr_handle_array[i] = Dummy_isr;
    }

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
