#include<stdio.h>
#include"lcd.h"
#include"frameBuffer.h"

void test_lcd_tft_8Bit_240_320(void)
{
    lcd_port_init();
    tft_lcd_init(MODE_8BIT_240_320);
    lcd_power_enable(0,1);
    lcd_envid_on_off(1);

    lcd_palette_8Bit_init();

    clear_screen(0x0);

    printf("TFT 8Bit\n");

    printf("1. Press any key to draw line\n");
    getc();

    draw_line(0,0,239,319,1);

    printf("2. Press any key to fill the screen with one color\n");
    getc();

    clear_screen(128);

    printf("3. Press any key to stop lcd testing\n");
    getc();
    lcd_envid_on_off(0);
}
