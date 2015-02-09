#include"lcd.h"

#define GPB0_MSK (3 << (0*2))
#define GPB1_OUT (1 << (0*2))

unsigned int fb_base_addr;
unsigned int bpp;
unsigned int xsize;
unsigned int ysize;

void lcd_port_init(void)
{
    GPCUP = 0xffffffff;
    GPCCON = 0xaaaaaaaa;
    GPDUP = 0xffffffff;
    GPDCON = 0xaaaaaaaa;

    // lcd power enable pin
    GPBCON &= ~(GPB0_MSK);
    GPBCON |= GPB0_OUT;
    // power off
    GPBDAT &= ~(1 << 0);
}
void tft_lcd_init(int type)
{
    switch(type)
    {
        case 8BIT_240_320:
            LCDCON1 = (CLKVAL_240_320 << 8) | (LCD_TYPE_TFT << 5) | \
                      (BPP_MODE_8BPP << 1) | (ENVID_DISABLE << 0);
            LCDCON2 = (VBPD_240_320 << 24) | (LINE_VAL_TFT_240_320 << 14) | \
                      (VFPD_240_320 << 6) | (VSPW_240_320 << 0);
            LCDCON3 = (HBPD_240_320 << 19) | (HOZ_VAL_TFT_240_320 << 8) | \
                      (HFPD_240_320 << 0);
            LCDCON4 = (HSPW_240_320 << 0);
            LCDCON5 = (FORMAT_8BPP_565 << 11) | (HSYNC_INV << 9) | (VSYNC_INV << 8) | \
                      (BSWP << 1);
            // the start address
            LCDSADDR1 = ((LCD_FRAME_BUFFER >> 22) << 21) | LOWER_21BITS(LCD_FRAME_BUFFER >> 1);
            // the end address
            LCDSADDR2 = LOWER_21BITS((LCD_FRAME_BUFFER + LCD_YSIZE_TFT_240_320 * LCD_XSIZE_TFT_240_320*1) >> 1);

            LCDSADDR3 = (OFFSIZE << 11) | (LCD_XSIZE_TFT_240_320/2);

            // disable palette
            TPAL = 0;

            fb_base_addr = LCD_FRAME_BUFFER;
            bpp = 8;
            xsize = 240;
            ysize = 320;

            break;
        case 16BIT_240_320:
            break;
        case 8BIT_640_480:
            break;
        case 16BIT_640_480:
            break;
        default:
            break;
    }
}
