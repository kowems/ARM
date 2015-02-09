#include"uart.h"
#include"stdio.h"

void open_uart(void);

int main(void)
{
    char c;

    open_uart();

    printf("\r\n########Test TFT LCD #########\r\n");

    printf("1 TFT240320 8Bit\n\r");
    printf("2 TFT240320 16Bit\n\r");

    printf("Please type your selection:");
    scanf("%c",&c);
    printf("%c\n\r",c);

    switch(c)
    {
        case '1':
            break;
        case '2':
            break;
        default:
            break;
    }
    
    return 0;
}

void open_uart(void)
{
    uart_init();
}
