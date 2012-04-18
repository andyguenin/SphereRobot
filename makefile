all: I2CCom.c
	cd java-c-integration
	javac I2CCom
	javah I2CCom
	gcc -Wall -fPIC -c I2CCom.c -I/usr/lib/jvm/java-6-openjdk/include -I/usr/lib/jvm/java-6-openjdk/include/linux 
	gcc -shared -Wl,-soname,libi2ccom.so.1 -o libi2ccom.so.1.0 I2CCom.o
	mkdir -p /usr/lib/revo
	mv libi2ccom.so.1.0 /usr/lib/revo
	ldconfig -n /usr/lib/revo	
	ln -sf /usr/lib/revo/libi2ccom.so.1.0 /usr/lib/revo/libi2ccom.so
	rm -f I2CCom.o I2CCom.h
	cd ..
clean:
	rm -f lib*	
