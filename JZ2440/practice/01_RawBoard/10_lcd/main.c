#include"uart.h"
#include"stdio.h"
#include"lcdLib.h"

int main(void)
{
    char c;

    uart_init();
    printf("\r\n########Test TFT LCD #####\r\n");

    while(1)
    {
        printf("1. TFT 240 320 8Bit\n\r");
        printf("2. TFT 240 320 16Bit\n\r");
        printf("Please type your selection:");

        c = getc();
        printf("%d",c);
        switch(c)
        {
            case '1':
                test_lcd_tft_8Bit_240_320();
                break;
            case '2':
                break;
            default:
                break;
        }
    }

    return 0;
}
