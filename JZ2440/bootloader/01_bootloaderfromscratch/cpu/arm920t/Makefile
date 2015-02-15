objs := init.o interrupt.o

cpu.a: $(objs)
	$(AR) -r -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o:%.S
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(objs)
