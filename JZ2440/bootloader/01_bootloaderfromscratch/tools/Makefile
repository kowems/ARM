libs := libc.a

tool.a: $(libs)
	cd lib;make;mv libc.a ../tool.a;cd ..

clean:
	cd lib;make clean;cd ..
	rm -f tool.a *.o
