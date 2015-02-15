objs := armlinux.o board.o

lib_arm.a:$(objs)
	$(AR) -r -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f lib_arm.a $(objs)
