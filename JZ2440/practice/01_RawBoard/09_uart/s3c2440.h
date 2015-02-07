
#define WTCON       (*(volatile unsigned long *)0x53000000)

/* GPIO registers */
#define GPFCON      (*(volatile unsigned long *)0x56000050)
#define GPFDAT      (*(volatile unsigned long *)0x56000054)
#define GPFUP       (*(volatile unsigned long *)0x56000058)

#define GPHCON      (*(volatile unsigned long *)0x56000070)
#define GPHDAT      (*(volatile unsigned long *)0x56000074)
#define GPHUP       (*(volatile unsigned long *)0x56000078)

#define GPGCON      (*(volatile unsigned long *)0x56000060)
#define GPGDAT      (*(volatile unsigned long *)0x56000064)
#define GPGUP       (*(volatile unsigned long *)0x56000068)
/* interrupt registers */
#define SRCPND      (*(volatile unsigned long *)0x4A000000)
#define INTMOD      (*(volatile unsigned long *)0x4A000004)
#define INTMSK      (*(volatile unsigned long *)0x4A000008)
#define PRIORITY    (*(volatile unsigned long *)0x4A00000c)
#define INTPND      (*(volatile unsigned long *)0x4A000010)
#define INTOFFSET   (*(volatile unsigned long *)0x4A000014)
#define SUBSRCPND   (*(volatile unsigned long *)0x4A000018)
#define INTSUBMSK   (*(volatile unsigned long *)0x4A00001c)

/* external interrupt registers */
#define EINTMASK    (*(volatile unsigned long *)0x560000a4)
#define EINTPEND    (*(volatile unsigned long *)0x560000a8)

/* clock registers */
#define LOCKTIME    (*(volatile unsigned long *)0x4c000000)
#define MPLLCON     (*(volatile unsigned long *)0x4c000004)
#define CLKDIVN     (*(volatile unsigned long *)0x4c000014)

/* UART registers */
#define ULCON0      (*(volatile unsigned long *)0x50000000)
#define UCON0       (*(volatile unsigned long *)0x50000004)
#define UFCON0      (*(volatile unsigned long *)0x50000008)
#define UFSTAT0     (*(volatile unsigned long *)0x50000018)
#define UTXH0       (*(volatile unsigned long *)0x50000020)
#define URXH0       (*(volatile unsigned long *)0x50000024)
#define UBRDIV0     (*(volatile unsigned long *)0x50000028)
