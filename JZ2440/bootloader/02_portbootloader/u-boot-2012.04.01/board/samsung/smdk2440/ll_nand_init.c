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

/* Nand flash registers */
#define NFCONF      (*(volatile unsigned long *)0x4e000000)
#define NFCONT      (*(volatile unsigned long *)0x4e000004)
#define NFCMD       (*(volatile unsigned long *)0x4e000008)
#define NFADDR      (*(volatile unsigned long *)0x4e00000c)
#define NFDATA      (*(volatile unsigned long *)0x4e000010)
#define NFMECCD0    (*(volatile unsigned long *)0x4e000014)
#define NFMECCD1    (*(volatile unsigned long *)0x4e000018)
#define NFSECCD     (*(volatile unsigned long *)0x4e00001c)
#define NFSTAT      (*(volatile unsigned long *)0x4e000020)
#define NFESTAT0    (*(volatile unsigned long *)0x4e000024)
#define NFESTAT1    (*(volatile unsigned long *)0x4e000028)
#define NFMECC0     (*(volatile unsigned long *)0x4e00002c)
#define NFMECC1     (*(volatile unsigned long *)0x4e000030)
#define NFSECC      (*(volatile unsigned long *)0x4e000034)
#define NFSBLK      (*(volatile unsigned long *)0x4e000038)
#define NFEBLK      (*(volatile unsigned long *)0x4e00003c)

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

static void nand_reset(void);
static void nand_select_chip(void);
static void nand_deselect_chip(void);
static void wait_idle(void);
static void write_cmd(unsigned char cmd);
static void write_addr(unsigned int addr);
static unsigned char read_data(void);

void ll_nand_init(void)
{
    // set cycle
    NFCONF = (TACLS << 12)|(TWRPH0 << 8)|(TWRPH1 << 4);
    // enable nand flash controller init ECC disable chip select
    NFCONT = (INIT_ECC << 4)|(CE << 1)|(MODE << 0);

    // reset nand flash
    // nand_reset();
}
static void nand_reset(void)
{
    nand_select_chip();
    write_cmd(0xff);
    wait_idle();
    nand_deselect_chip();
}
static void nand_select_chip(void)
{
    NFCONT &= ~(1 << 1);
    delay();
}
static void nand_deselect_chip(void)
{
    NFCONT |= (1 << 1);
}
static void wait_idle(void)
{
#if 1
    volatile unsigned char *p = (volatile unsigned char *)&NFSTAT;
    while(!(*p & IS_NAND_BUSY))
            delay();
#else
    while(!(NFSTAT & 1));
#endif
}
static void write_cmd(unsigned char cmd)
{
    NFCMD = cmd;
    delay();
}

static void write_addr(unsigned int addr)
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
static unsigned char read_data(void)
{
#if 1
    volatile unsigned char *p = (volatile unsigned char *)&NFDATA;
    return *p;
#else
    // it can not get data;I have no idea why
    return (volatile unsigned char)NFDATA;
#endif
}
void ll_nand_read(unsigned char *buf,unsigned int start_addr,unsigned int size)
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
        ll_nand_read(dest,src,len);
    }
}
