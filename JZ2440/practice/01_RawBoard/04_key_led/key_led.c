#define GPFCON	(*(volatile unsigned long *)0x56000050)
#define GPFDAT	(*(volatile unsigned long *)0x56000054)

#define GPGCON	(*(volatile unsigned long *)0x56000060)
#define GPGDAT	(*(volatile unsigned long *)0x56000064)

#define GPF4_mask (3 << (4*2))
#define GPF5_mask (3 << (5*2))
#define GPF6_mask (3 << (6*2))

#define GPF4_out (1 << (4*2))
#define GPF5_out (1 << (5*2))
#define GPF6_out (1 << (6*2))

#define GPF0_mask (3 << (0*2))
#define GPF2_mask (3 << (2*2))
#define GPG3_mask (3 << (3*2))

#define GPF0_in (0 << (0*2))
#define GPF2_in (0 << (2*2))
#define GPG3_in (0 << (3*2))

int main(void)
{
	unsigned long dat = 0xffffffff;

	GPFCON &= ~(GPF4_mask | GPF5_mask | GPF6_mask);
	GPFCON |= (GPF4_out | GPF5_out | GPF6_out);

	GPFCON &= ~(GPF0_mask | GPF2_mask);
	GPFCON |= (GPF0_in | GPF2_in);

	GPGCON &= ~(GPG3_mask);
	GPGCON |= GPG3_in;

	while(1){
		dat = GPFDAT;

		if(dat & (1 << 0))
			GPFDAT |= (1 << 4);
		else
			GPFDAT &= ~(1 << 4);

		if(dat & (1 << 2))
			GPFDAT |= (1 << 5);
		else
			GPFDAT &= ~(1 << 5);

		dat = GPGDAT;

		if(dat & (1 << 3))
			GPFDAT |= (1 << 6);
		else
			GPFDAT &= ~(1 << 6);
	}

	return 0;
}
