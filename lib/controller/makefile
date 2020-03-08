output: libcontrol.o control.o

libcontrol.o: control.o
	gcc -shared -o libcontrol.so -fPIC control.c

control.o: control.c
	gcc  control.c

clean:
	rm *.so *.o *.out
