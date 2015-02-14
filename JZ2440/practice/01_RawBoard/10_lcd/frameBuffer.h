#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include<types.h>

void put_pixel(UINT32 x,UINT32 y,UINT32 color);

void draw_line(INT32 x1,INT32 y1,INT32 x2,INT32 y2,UINT32 color);

void clear_screen(UINT32 color);

#endif
