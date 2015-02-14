#include "frameBuffer.h"

extern unsigned int fb_base_addr;
extern unsigned int bpp;
extern unsigned int xsize;
extern unsigned int ysize;

void put_pixel(UINT32 x,UINT32 y,UINT32 color)
{
    //UINT8 red,green,blue;
    UINT8 *addr;

    switch(bpp)
    {
        case 16:
            break;
        case 8:
            addr = (UINT8*)fb_base_addr + ((y-1) * xsize + x);
            *addr = (UINT8)color;
            break;
        default:
            break;
    }
}
void draw_line(INT32 x1,INT32 y1,INT32 x2,INT32 y2,UINT32 color)
{
    int dx,dy,e;
    dx = x2 - x1;
    dy = y2 - y1;

    if(dx >= 0)
    {
        if(dy >= 0)
        {
            if(dx >= dy)
            {
                e = dy - dx/2;
                while(x1 <= x2)
                {
                    put_pixel(x1,y1,color);
                    if(e > 0)
                    {
                        y1 += 1;
                        e -= dx;
                    }
                    x1 += 1;
                    e += dy;
                }
            }else{
                e = dx - dy/2;
                while(y1 <= y2)
                {
                    put_pixel(x1,x2,color);
                    if(e > 0)
                    {
                        x1 += 1;
                        e -= dy;
                    }
                    y1 += 1;
                    e += dx;
                }
            }
        }else{
            dy = -dy;

            if(dx >= dy)
            {
                e = dy - dx/2;
                while(x1 <= x2)
                {
                    put_pixel(x1,y1,color);
                    if(e > 0)
                    {
                        y1 -= 1;
                        e -= dx;
                    }
                    x1 += 1;
                    e += dy;
                }
            }else{
                e = dx - dy/2;
                while(y1 >= y2)
                {
                    put_pixel(x1,y1,color);
                    if(e > 0)
                    {
                        x1 += 1;
                        e -= dy;
                    }
                    y1 -= 1;
                    e += dx;
                }
            }
        }
    }else{
        dx = -dx;
        if(dy >= 0)
        {
            if(dx >= dy)
            {
                e = dy - dx/2;
                while(x1 >= x2)
                {
                    put_pixel(x1,y1,color);
                    if(e > 0)
                    {
                        y1 += 1;
                        e -= dx;
                    }   
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 3/8 octant
            {
                e=dx-dy/2;
                while(y1<=y2)
                {
                    put_pixel(x1,y1,color);
                    if(e>0){x1-=1;e-=dy;}   
                    y1+=1;
                    e+=dx;
                }
            }
        }
        else           // dy<0
        {
            dy=-dy;   // dy=abs(dy)

            if(dx>=dy) // 5/8 octant
            {
                e=dy-dx/2;
                while(x1>=x2)
                {
                    put_pixel(x1,y1,color);
                    if(e>0){y1-=1;e-=dx;}   
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 6/8 octant
            {
                e=dx-dy/2;
                while(y1>=y2)
                {
                    put_pixel(x1,y1,color);
                    if(e>0){x1-=1;e-=dy;}   
                    y1-=1;
                    e+=dx;
                }
            }
        }   
    }
}

void clear_screen(UINT32 color)
{
    UINT32 x,y;

    for(y = 0; y < ysize; y++)
        for(x = 0; x < xsize; x++)
            put_pixel(x,y,color);
}
