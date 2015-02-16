libs := nand.a uart.a

driver.a:$(libs)
	$(AR) -x nand.a
	$(AR) -x uart.a
	$(AR) -r -o $@ *.o

.PHONY : nand.a
nand.a:
	cd nand;make;mv nand.a ..;cd ..

.PHONY : uart.a
uart.a:
	cd uart;make;mv uart.a ..;cd ..

clean:
	cd nand;make clean;cd ..
	cd uart;make clean;cd ..
	rm -f *.a *.o
