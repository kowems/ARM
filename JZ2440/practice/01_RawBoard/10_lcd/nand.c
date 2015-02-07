#include"s3c2440.h"

#define TACLS 0
#define TWRPH0 3
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
void write_cmd(int cmd);
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
    volatile unsigned char *p = (volatile unsigned char *)&NFSTAT;
    while(!(*p & IS_NAND_BUSY))
            delay();
}
void write_cmd(int cmd)
{
    NFCMD = cmd;
}

void write_addr(unsigned int addr)
{
    int col,page;

    col = addr & NAND_BLOCK_MASK;
    page = addr / NAND_SECTOR_SIZE;

    NFADDR = col & 0xff;
    delay();
    NFADDR = (col >> 8) & 0x0f;
    delay();
    NFADDR = page & 0xff;
    delay();
    NFADDR = (page >> 8) & 0xff;
    delay();
    NFADDR = (page >> 16) & 0x03;
    delay();
}
unsigned char read_data(void)
{
#if 1
    volatile unsigned char *p = (volatile unsigned char *)&NFDATA;
    return *p;
#else
    // it can not get data;I have no idea
    return (volatile unsigned char)NFDATA;
#endif
}
void nand_read(unsigned char *buf,unsigned long start_addr,int size)
{
    int i,j;

    if((start_addr & NAND_BLOCK_MASK) || (size & NAND_BLOCK_MASK))
        return;
    
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
