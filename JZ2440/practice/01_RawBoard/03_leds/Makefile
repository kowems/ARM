CFLAGS := -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer -ffreestanding
leds.bin : leds.c start.S
	arm-linux-gcc $(CFLAGS) -g -c -o start.o start.S
	arm-linux-gcc $(CFLAGS) -g -c -o leds.o leds.c
	arm-linux-ld -Ttext 0x00000000 -g start.o leds.o -o leds_elf
	arm-linux-objcopy -O binary -S leds_elf leds.bin
	arm-linux-objdump -D -m arm leds_elf > leds.dis
clean:
	rm -f leds.bin leds_elf *.o leds.dis
