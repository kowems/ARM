objs := head.o init.o key_led.o

mmu.bin : $(objs)
	arm-linux-ld -Tmmu.lds -o mmu_elf $^
	arm-linux-objcopy -O binary -S mmu_elf $@
	arm-linux-objdump -D -m arm mmu_elf > mmu.dis

%.o:%.c
	arm-linux-gcc -Wall -O2 -c -o $@ $<

%.o:%.S
	arm-linux-gcc -Wall -O2 -c -o $@ $<

clean:
	rm -f *.o mmu.bin
