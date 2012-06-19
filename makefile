die : die.o
	gcc -o die die.o

die.o : die.c
	gcc -c die.c

clean :
	rm *.o
