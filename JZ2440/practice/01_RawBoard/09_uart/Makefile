objs := head.o init.o uart.o main.o interrupt.o led.o

uart_irq.bin:$(objs)
	arm-linux-ld -Tuart.lds -o uart.elf $^
	arm-linux-objcopy -O binary -S uart.elf $@
	arm-linux-objdump -D -m arm uart.elf > uart.dis

%.o:%.c
	arm-linux-gcc -Wall -O2 -c -o $@ $<
%.o:%.S
	arm-linux-gcc -Wall -O2 -c -o $@ $<

clean:
	rm -f uart_irq.bin uart.elf uart.dis *.o
