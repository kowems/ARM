/* Watch Dog register */
#define WTCON       (*(volatile unsigned long *)0x53000000)

/* SDRAM register */
#define MEM_CTL_BASE    0x48000000
#define SDRAM_BASE      0x30000000

/* GPIO registers */
#define GPBCON      (*(volatile unsigned long *)0x56000010)
#define GPBDAT      (*(volatile unsigned long *)0x56000014)
#define GPBUP       (*(volatile unsigned long *)0x56000018)

#define GPCCON      (*(volatile unsigned long *)0x56000020)
#define GPCDAT      (*(volatile unsigned long *)0x56000024)
#define GPCUP       (*(volatile unsigned long *)0x56000028)

#define GPDCON      (*(volatile unsigned long *)0x56000030)
#define GPDDAT      (*(volatile unsigned long *)0x56000034)
#define GPDUP       (*(volatile unsigned long *)0x56000038)

#define GPFCON      (*(volatile unsigned long *)0x56000050)
#define GPFDAT      (*(volatile unsigned long *)0x56000054)
#define GPFUP       (*(volatile unsigned long *)0x56000058)

#define GPGCON      (*(volatile unsigned long *)0x56000060)
#define GPGDAT      (*(volatile unsigned long *)0x56000064)
#define GPGUP       (*(volatile unsigned long *)0x56000068)

#define GPHCON      (*(volatile unsigned long *)0x56000070)
#define GPHDAT      (*(volatile unsigned long *)0x56000074)
#define GPHUP       (*(volatile unsigned long *)0x56000078)

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
#define UTRSTAT0    (*(volatile unsigned long *)0x50000010)
#define UFSTAT0     (*(volatile unsigned long *)0x50000018)
#define UTXH0       (*(volatile unsigned long *)0x50000020)
#define URXH0       (*(volatile unsigned long *)0x50000024)
#define UBRDIV0     (*(volatile unsigned long *)0x50000028)

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

/* LCD CONTROLLER */
#define LCDCON1     (*(volatile unsigned long *)0x4d000000)
#define LCDCON2     (*(volatile unsigned long *)0x4d000004)
#define LCDCON3     (*(volatile unsigned long *)0x4d000008)
#define LCDCON4     (*(volatile unsigned long *)0x4d00000c)
#define LCDCON5     (*(volatile unsigned long *)0x4d000010)
#define LCDSADDR1   (*(volatile unsigned long *)0x4d000014)
#define LCDSADDR2   (*(volatile unsigned long *)0x4d000018)
#define LCDSADDR3   (*(volatile unsigned long *)0x4d00001c)
#define REDLUT      (*(volatile unsigned long *)0x4d000020)
#define GREENLUT    (*(volatile unsigned long *)0x4d000024)
#define BLUELUT     (*(volatile unsigned long *)0x4d000028)
#define DITHMODE    (*(volatile unsigned long *)0x4d00004c)
#define TPAL        (*(volatile unsigned long *)0x4d000050)
