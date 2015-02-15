objs := nand.o

nand.a: $(objs)
	$(AR) -r -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(objs)
