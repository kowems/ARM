/*
 * uart - uart code for ARM 2440
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
 *   01/15/2015 Eric: initialization creation
 *
 */

/**********************************************************
 *
 * File: uart.c
 * Function: uart send or receive data
 *
 *********************************************************/
#include"asm/arch_s3c24x0/hardware.h"

extern int printf(const char *fmt, ...);

#define RXD0READY   (1)
#define TXD0READY   (1 << 2)

#define PCLK        50000000
#define UART_CLK    PCLK
#define UART_BAUD_RATE  115200
#define UART_BRD        ((UART_CLK / (UART_BAUD_RATE * 16)) - 1)

#define TX_BUF_LEN 2048

struct ringBuf {
    unsigned char * buf;
    unsigned int r_idx;
    unsigned int w_idx;
};
static unsigned char tb[TX_BUF_LEN];

struct ringBuf tx_buf = {tb,0,0};

static int getData(unsigned char *pData);

#ifdef ENABLE_IRQ
void uart_init(void)
{
    //GPHCON &= ~((0x3 << 4) | (0x3 << 6));
    GPHCON |= ((0x2 << 4) | (0x2 << 6));    // set GPH2 & GPH3 as uart
    GPHUP = 0x0c;           // set pull up resister
    //GPHUP = 0xf0;

    ULCON0 = 0x03;          // 8N1

    UCON0 = 0x05 | (1 << 9);// interrupt,URAT clock sources is PCLK

    UFCON0 = 0x41;          // Tx FIFO Trigger Level 16-byte, Rx FIFO Trgger Level 32 byte, enable FIFO

    UBRDIV0 = UART_BRD;     // baud rate 115200

    INTMOD = 0x00;

    INTMSK &= ~(1 << 28);

    INTSUBMSK &= ~0x1;
}
#else
// It is non-irq mode
void uart_init(void)
{
    GPHCON  |= 0xa0;    // make GPH2,GPH3 as TXD0,RXD0
    GPHUP   = 0x0c;     // GPH2,GPH3 pull-up resistor

    ULCON0  = 0x03;     // 8N1(8 data bit,no parity bit,1 stop bit)
    UCON0   = 0x05;     // polling mode,UART clock source is PCLK
    UFCON0  = 0x00;     // unuse FIFO
    UMCON0  = 0x00;     // unuse fluid control
    UBRDIV0 = UART_BRD; // set baut rate as 115200
}
#endif

void uart_disable_tx_irq(void)
{
    INTSUBMSK |= (0x1 << 1);  // issue : INTSUBMSK |= (0x1 << 2);
}

void uart_enable_tx_irq(void)
{
    INTSUBMSK &= ~(0x1 << 1);
}

static inline int isFull(struct ringBuf *it)
{
    if((it->w_idx + 1) % TX_BUF_LEN == it->r_idx)
        return 1;
    else
        return 0;
}

static inline int isEmpty(struct ringBuf *it)
{
    return (it->w_idx == it->r_idx);
}

void uart_irq(void)
{
    int cnt = 0,i = 0;
    unsigned char c = 0;

    if(SUBSRCPND & (0x1 << 1)) {  // send interrupt
        cnt = 64 - (int)((UFSTAT0 >> 8) & 0x3f);
        for(i = 0;i < cnt;i++){
            if(getData(&c) == 0)
                UTXH0 = c;
            else
                break;
        }
        SUBSRCPND |= 1 << 1;
#if 1
    }else if(SUBSRCPND & (0x1 << 0)) { // receive interrupt
#else
    }else { // receive interrupt
#endif
        /* need more code to do receive action */
        SUBSRCPND |= 1 << 0;
    }

    SRCPND |= 1 << 28;
    INTPND |= 1 << 28;
    
}
static int getData(unsigned char *pData)
{
    if(!isEmpty(&tx_buf))
    {
        *pData = tx_buf.buf[tx_buf.r_idx];
        tx_buf.r_idx = (tx_buf.r_idx + 1) % TX_BUF_LEN;
        return 0;
    }else{
        uart_disable_tx_irq();
        return -1;
    }
}

static int putData(unsigned char data)
{
    if(!isFull(&tx_buf)){
        tx_buf.buf[tx_buf.w_idx] = data;
        tx_buf.w_idx = (tx_buf.w_idx + 1) % TX_BUF_LEN;
        return 0;
    }else{
        return -1;
    }
}
#ifdef ENABLE_IRQ
void putc(char c)
{
    putData(c);

    uart_enable_tx_irq();
}
#else
// It is non-irq mode.
void putc(unsigned char c)
{
    while(!(UTRSTAT0 & TXD0READY));

    UTXH0 = c;
}
#endif

#ifdef ENABLE_IRQ
#else
unsigned char getc(void)
{
    while(!(UTRSTAT0 & RXD0READY));

    return URXH0;
}
#endif

void puthex(unsigned int val)
{
	/* 0x1234abcd */
	int i;
	int j;
	
	putc('0');
	putc('x');

	for (i = 0; i < 8; i++)
	{
		j = (val >> ((7-i)*4)) & 0xf;
		if ((j >= 0) && (j <= 9))
			putc('0' + j);
		else
			putc('A' + j - 0xa);
		
	}
	
}
