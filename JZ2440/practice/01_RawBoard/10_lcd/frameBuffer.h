#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include"types.h"

void put_pixel(UINT32 x,UINT32 y,UINT32 color);

void draw_line(int x1,int y1,int x2,int y2,int color);

void clear_screen(UINT32 color);

#endif
