CFLAGS = -lpthread 
CC = gcc
__start__: a.out
	./a.out 

a.out: main.o
	$(CC) main.o -o a.out $(CFLAGS)

main.o: main.c
	$(CC) -c -Wall -pedantic main.c $(CFLAGS)

