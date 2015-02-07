CFLAGS := -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer -ffreestanding
leds.bin : key_led.c start.S
	arm-linux-gcc $(CFLAGS) -g -c -o start.o start.S
	arm-linux-gcc $(CFLAGS) -g -c -o key_led.o key_led.c
	arm-linux-ld -Ttext 0x00000000 -g start.o key_led.o -o key_led_elf
	arm-linux-objcopy -O binary -S key_led_elf key_led.bin
	arm-linux-objdump -D -m arm key_led_elf > key_led.dis
clean:
	rm -f key_led.bin key_led_elf *.o key_led.dis
