CC = gcc

default: control.a

control.a: control.o
	ar rcs $@ $^

control.o: control.c control.h
	$(CC) -c $<

clean:
	rm *.o *.a
