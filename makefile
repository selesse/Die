die : die.o
	gcc -o die die.o

die.o : die.c
	gcc -c -Wall die.c

clean :
	rm *.o
