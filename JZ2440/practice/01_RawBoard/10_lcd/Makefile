CC = arm-linux-gcc
LD = arm-linux-ld
AR = arm-linux-ar
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump

INCLUDEDIR := $(shell pwd)/include
FLAGS := -Wall -O2 -nostdinc -I$(INCLUDEDIR)

export CC LD AR OBJCOPY OBJDUMP INCLUDEDIR FLAGS

objs := head.o init.o uart.o nand.o main.o interrupt.o led.o lib/libc.a frameBuffer.o lcdLib.o lcd.o

elf = lcd.elf

lcd.bin:$(objs)
	${LD} -Tlcd.lds -o ${elf} $^
	${OBJCOPY} -O binary -S ${elf} $@
	${OBJDUMP} -D -m arm ${elf} > lcd.dis

.PHONY : lib/libc.a
lib/libc.a:
	cd lib;make;cd ..

%.o:%.c
	${CC} $(FLAGS) -c -o $@ $<
%.o:%.S
	${CC} $(FLAGS) -c -o $@ $<

clean:
	make clean -C lib
	rm -f lcd.bin ${elf} lcd.dis *.o
