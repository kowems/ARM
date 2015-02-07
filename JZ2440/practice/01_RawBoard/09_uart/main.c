#include"uart.h"
#include"led.h"

int main(void)
{
    unsigned char *str = "Hello World";
    int i = 0;

    led_on();
    for(i = 0;i < 12;i++){
        if(str[i] != '\n')
            putc(str[i]);
    }
    return 0;
}
