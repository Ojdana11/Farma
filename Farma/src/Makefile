CFLAGS = -lpthread -lncurses
CC = g++
__start__: a.out
	./a.out 8 6

a.out: program.o generator.o watekrolnik.o rysowanie.o straznik.o
	$(CC) program.o generator.o watekrolnik.o rysowanie.o straznik.o -o a.out $(CFLAGS)

program.o: program.cpp rysowanie.h straznik.h generator.h
	$(CC) -c -Wall -pedantic program.cpp $(CFLAGS)

rysowanie.o: rysowanie.h rysowanie.cpp
		$(CC) -c -Wall -pedantic rysowanie.cpp $(CFLAGS)

generator.o: generator.h watekrolnik.h generator.cpp
		$(CC) -c -Wall -pedantic generator.cpp $(CFLAGS)

watekrolnik.o: watekrolnik.h watekrolnik.cpp
		$(CC) -c -Wall -pedantic watekrolnik.cpp $(CFLAGS)

straznik.o: straznik.h straznik.cpp
		$(CC) -c -Wall -pedantic straznik.cpp $(CFLAGS)
