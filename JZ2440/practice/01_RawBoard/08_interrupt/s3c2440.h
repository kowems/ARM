
#define WTCON       (*(volatile unsigned long *)0x53000000)

/* GPIO registers */
#define GPFCON      (*(volatile unsigned long *)0x56000050)
#define GPFDAT      (*(volatile unsigned long *)0x56000054)
#define GPFUP       (*(volatile unsigned long *)0x56000058)

#define GPGCON      (*(volatile unsigned long *)0x56000060)
#define GPGDAT      (*(volatile unsigned long *)0x56000064)
#define GPGUP       (*(volatile unsigned long *)0x56000068)
/* interrupt registers */
#define SRCPND      (*(volatile unsigned long *)0x4A000000)
#define INTMSK      (*(volatile unsigned long *)0x4A000008)
#define PRIORITY    (*(volatile unsigned long *)0x4A00000c)
#define INTPND      (*(volatile unsigned long *)0x4A000010)
#define INTOFFSET   (*(volatile unsigned long *)0x4A000014)

/* external interrupt registers */
#define EINTMASK    (*(volatile unsigned long *)0x560000a4)
#define EINTPEND    (*(volatile unsigned long *)0x560000a8)
