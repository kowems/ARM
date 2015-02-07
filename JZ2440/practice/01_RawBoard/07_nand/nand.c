#include<stdio.h>
#include<stdlib.h>

#define NAND_BUSY 1
#define delay()   do { int i = 0; for(i = 0;i < 10;i++); }while(0)

#define TACLS 0
#define TWRPH0 3
#define TWRPH1 0

typedef unsigned int S3C24X0_REG32;

typedef struct {
    S3C24X0_REG32    NFCONF;
    S3C24X0_REG32    NFCONT;
    S3C24X0_REG32    NFCMD;
    S3C24X0_REG32    NFADDR;
    S3C24X0_REG32    NFDATA;
    S3C24X0_REG32    NFMECCD0;
    S3C24X0_REG32    NFMECCD1;
    S3C24X0_REG32    NFSECCD;
    S3C24X0_REG32    NFSTAT;
    S3C24X0_REG32    NFESTAT0;
    S3C24X0_REG32    NFESTAT1;
    S3C24X0_REG32    NFMECC0;
    S3C24X0_REG32    NFMECC1;
    S3C24X0_REG32    NFSECC;
    S3C24X0_REG32    NFSBLK;
    S3C24X0_REG32    NFEBLK;
} S3C2440_NAND;

static S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;

// function definitions
// interface definitions
void nand_init(void);
void nand_read(unsigned char *buf,unsigned long start_addr,int size);

// inner method definitions
static void nand_reset(void);
static void nand_select_chip(void);
static void nand_deselect_chip(void);
static void wait_idle(void);
static void write_cmd(unsigned char cmd);
static void write_addr(unsigned int addr);
static unsigned char read_data(void);

void nand_init(void)
{
    s3c2440nand->NFCONF = (TACLS << 12) | (TWRPH0 << 8) | (TWRPH1 << 4);
    s3c2440nand->NFCONT = (1 << 4) | (1 << 1) | (1 << 0);
    
    nand_reset();
}

void nand_read(unsigned char *buf,unsigned long start_addr,int size)
{
    unsigned int addr = 0,j = 0;
    int tmp_size = size;
    
    if(NULL != buf && size > 0){
	nand_select_chip();
	// send read0 command
	for(addr = start_addr;addr < (start_addr + size);){
	    write_cmd(0);
	    write_addr(start_addr);
	    write_cmd(0x30);
	    wait_idle();
	
	    for(j = 0;j < 2048 && j <= tmp_size;j++,addr++){
            *(buf++) = read_data();
	        tmp_size--;
	    }
	}
    }
}

static void nand_reset(void)
{
    nand_select_chip();
    write_cmd(0xff);	// reset nand flash
    wait_idle();
    nand_deselect_chip();
}

static void nand_select_chip(void)
{
    s3c2440nand->NFCONT &= ~(1 << 1);

    delay();
}

static void nand_deselect_chip(void)
{
    s3c2440nand->NFCONT |= (1 << 1);
}

static void wait_idle(void)
{
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFSTAT;

    while(!(*p & NAND_BUSY))
	delay();
}

static void write_cmd(unsigned char cmd)
{
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFCMD;

    *p = cmd;
}

static void write_addr(unsigned int addr)
{
    unsigned int col = 0,page = 0;
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFADDR;

    col = addr & 2047;
    page = addr / 2048;

    *p = col & 0xff;		// Column A0~A7
    delay();
    *p = (col >> 8) & 0x0f;	// Column A8~A11
    delay();
    *p = page & 0xff;		// Row A12~A19
    delay();
    *p = (page >> 8) & 0xff;	// Row A20~A27
    delay();
    *p = (page >> 16) & 0x03;	// Row A28~A29
    delay();
}

static unsigned char read_data(void)
{
    volatile unsigned char *p = (volatile unsigned char*)&s3c2440nand->NFDATA;

    return *p;
}
