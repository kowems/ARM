objs := head.o main.o nand.o

nand.bin : $(objs)
	arm-linux-ld -Tnand.lds -o nand_elf $^
	arm-linux-objcopy -O binary -S nand_elf $@
	arm-linux-objdump -D -m arm nand_elf > nand.dis

%.o:%.c
	arm-linux-gcc -Wall -c -O2 -o $@ $<

%.o:%.S
	arm-linux-gcc -Wall -c -O2 -o $@ $<

clean:
	rm -rf nand.dis nand.bin nand_elf *.o


