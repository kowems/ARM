/*
 * nand - code for nand flash K9F2G08U0C
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

#include"asm/arch_s3c24x0/hardware.h"

#define TACLS 0
#if 0
#define TWRPH0 3
#else
#define TWRPH0 1
#endif
#define TWRPH1 0

#define INIT_ECC 1
#define CE 1
#define MODE 1

#define IS_NAND_BUSY    1
#define NAND_BLOCK_MASK     (NAND_SECTOR_SIZE - 1)
#define NAND_SECTOR_SIZE    2048

#define delay()     do{int i = 0; for(i = 0;i < 10;i++);}while(0)

void nand_reset(void);
void nand_select_chip(void);
void nand_deselect_chip(void);
void wait_idle(void);
void write_cmd(unsigned char cmd);
void write_addr(unsigned int addr);
unsigned char read_data(void);

void nand_init(void)
{
    // set cycle
    NFCONF = (TACLS << 12)|(TWRPH0 << 8)|(TWRPH1 << 4);
    // enable nand flash controller init ECC disable chip select
    NFCONT = (INIT_ECC << 4)|(CE << 1)|(MODE << 0);

    // reset nand flash
    nand_reset();
}
void nand_reset(void)
{
    nand_select_chip();
    write_cmd(0xff);
    wait_idle();
    nand_deselect_chip();
}
void nand_select_chip(void)
{
    NFCONT &= ~(1 << 1);
    delay();
}
void nand_deselect_chip(void)
{
    NFCONT |= (1 << 1);
}
void wait_idle(void)
{
#if 1
    volatile unsigned char *p = (volatile unsigned char *)&NFSTAT;
    while(!(*p & IS_NAND_BUSY))
            delay();
#else
    while(!(NFSTAT & 1));
#endif
}
void write_cmd(unsigned char cmd)
{
    NFCMD = cmd;
    delay();
}

void write_addr(unsigned int addr)
{
    unsigned int col,page;

    col = addr % NAND_SECTOR_SIZE;
    page = addr / NAND_SECTOR_SIZE;

    NFADDR = col & 0xff;
    delay();
    NFADDR = (col >> 8) & 0xff;
    delay();
    NFADDR = page & 0xff;
    delay();
    NFADDR = (page >> 8) & 0xff;
    delay();
    NFADDR = (page >> 16) & 0xff;
    delay();
}
unsigned char read_data(void)
{
#if 1
    volatile unsigned char *p = (volatile unsigned char *)&NFDATA;
    return *p;
#else
    // it can not get data;I have no idea why
    return (volatile unsigned char)NFDATA;
#endif
}
#if 1
void nand_read(unsigned char *buf,unsigned int start_addr,unsigned int size)
{
    int col = start_addr % 2048;
    unsigned int i = 0;

    nand_select_chip();
    
    while(i < size){
        // send READ command 1st Cycle
        write_cmd(0x00);
        // write address
        write_addr(start_addr);
        // send READ command 2nd Cycle
        write_cmd(0x30);
        // wait nand to idle
        wait_idle();

        for(;(col < NAND_SECTOR_SIZE) && (i < size);col++){
            buf[i] = read_data();
            i++;
            start_addr++;
        }
        col = 0;
    }

    nand_deselect_chip();

    return;
}
#else
// Below function is wrong,when start_addr is not at starting of page. 
void nand_read(unsigned char *buf,unsigned long start_addr,int size)
{
    int i,j;

    nand_select_chip();
    
    for(i = start_addr;i < (start_addr + size);){
        // send READ command 1st Cycle
        write_cmd(0);
        // write address
        write_addr(i);
        // send READ command 2nd Cycle
        write_cmd(0x30);
        // wait nand to idle
        wait_idle();

        for(j = 0;j < NAND_SECTOR_SIZE;j++,i++){
            *buf = read_data();
            buf++;
        }
    }

    nand_deselect_chip();

    return;
}
#endif
