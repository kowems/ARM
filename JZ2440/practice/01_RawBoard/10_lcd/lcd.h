#include<types.h>

#define LOWER_21BITS(n) ((n)&0x1fffff)

#define CLKVAL_240_320 (4)

#define LCD_TYPE_TFT (0x3)

#define BPP_MODE_8BPP (0xB)

#define ENVID_DISABLE (0)

#define VBPD_240_320 ((6-1)&0xff)

#define LCD_XSIZE_TFT_240_320 (240)
#define LCD_YSIZE_TFT_240_320 (320)
#define LINE_VAL_TFT_240_320 (LCD_YSIZE_TFT_240_320 - 1)
#define HOZ_VAL_TFT_240_320  (LCD_XSIZE_TFT_240_320 - 1)

#define VFPD_240_320 ((4-1)&0xff)

#define VSPW_240_320 ((2-1)&0x3f)

#define HBPD_240_320 ((11-1)&0x7f)


#define HFPD_240_320 ((2-1)&0xff)

#define HSPW_240_320 ((1-1)&0xff)

#define FORMAT_8BPP_565 (1)

#define HSYNC_INV (1)

#define VSYNC_INV (1)

#define BSWP (0)

#define LCD_FRAME_BUFFER 0x30400000

#define OFFSIZE (0)

#define PALETTE 0x4d000400

#define MODE_8BIT_240_320 0x4102
#define MODE_16BIT_240_320 0x4104

#define MODE_8BIT_640_480 0x4202
#define MODE_16BIT_640_480 0x4204

void lcd_port_init(void);
void tft_lcd_init(int type);
void lcd_power_enable(int invpwren,int pwren);
void lcd_envid_on_off(int on_off);
void lcd_palette_8Bit_init(void);
