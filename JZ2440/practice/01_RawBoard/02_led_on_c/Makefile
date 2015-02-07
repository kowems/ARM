led_on_c.bin : led_on_c.c start.S
	arm-linux-gcc -g -c -o start.o start.S
	arm-linux-gcc -g -c -o led_on_c.o led_on_c.c
	arm-linux-ld -Ttext 0x00000000 -g led_on_c.o start.o -o led_on_c_elf
	arm-linux-objcopy -O binary -S led_on_c_elf led_on_c.bin
	arm-linux-objdump -D -m arm led_on_c_elf > led_on_c.dis
clean:
	rm -f led_on_c.bin led_on_c_elf *.o led_on_c.dis
