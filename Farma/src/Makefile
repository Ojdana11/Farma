CFLAGS = -lpthread -lncurses
CC = g++
__start__: a.out
	./a.out 5 5

a.out: main.o generator.o watekrolnik.o
	$(CC) main.o generator.o watekrolnik.o -o a.out $(CFLAGS)

main.o: main.cpp generator.h
	$(CC) -c -Wall -pedantic main.cpp $(CFLAGS)

generator.o: generator.h watekrolnik.h generator.cpp
		$(CC) -c -Wall -pedantic generator.cpp $(CFLAGS)

watekrolnik.o: watekrolnik.h watekrolnik.cpp
		$(CC) -c -Wall -pedantic watekrolnik.cpp $(CFLAGS)
