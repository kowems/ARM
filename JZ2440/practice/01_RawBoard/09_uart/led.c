#include "s3c2440.h"

void led_on(void)
{
	GPFCON = 0x00000100;
	GPFDAT = 0x00000000;
}
