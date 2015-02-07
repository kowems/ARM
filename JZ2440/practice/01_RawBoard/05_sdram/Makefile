CFLAGS := -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer -ffreestanding
sdram.bin : key_led.c head.S
	arm-linux-gcc $(CFLAGS) -g -c -o head.o head.S
	arm-linux-gcc $(CFLAGS) -g -c -o key_led.o key_led.c
	arm-linux-ld -Ttext 0x00000000 -g head.o key_led.o -o key_led_elf
	arm-linux-objcopy -O binary -S key_led_elf sdram.bin
	arm-linux-objdump -D -m arm key_led_elf > sdram.dis
clean:
	rm -f sdram.bin key_led_elf *.o sdram.dis
