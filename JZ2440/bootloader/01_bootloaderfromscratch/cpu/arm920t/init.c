/*
 * init - init code for ARM
 *
 * Copyright (c) 2015 Eric Ju <Eric.X.Ju@gmail.com>
 * 
 * This program is free software;you can registribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation;Either version 2 of
 * the License,or (at your option) any later version.
 *
 */

/*                  History
 *
 *   01/14/2015 Eric: initialization creation
 *
 */

#include<nand.h>

int is_boot_from_Nor_flash()
{
    volatile int *p = (volatile int *)0;

    int val = *p;

    *p = 0x12345678;

    if(*p == 0x12345678){
        *p = val;
        return 0;
    }else{
        return 1;
    }
}

void copy_code_to_sdram(unsigned char *src,unsigned char *dest,unsigned int len)
{
    int i = 0;

    if(is_boot_from_Nor_flash()){
        while(i < len){
            dest[i] = src[i];
            i++;
        }
    }else{
        nand_read(dest,src,len);
    }
}
