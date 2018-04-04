
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include "generator.h"

#define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)

int main(int argc, char* argv[]) {
/*generowanie zmiennych losowych*/
	time_t tt;
	srand(time(&tt));

	if (argc == 3){
				printf("Liczba wątków: %d \n Liczba pól: %d\n", atoi(argv[1]), atoi(argv[2]));
		}
	else {
		puts("Niepoprawna liczba argumentów");
		return EXIT_FAILURE;
	}
	int watki = atoi(argv[1]);
	int pola = atoi(argv[2]);

tworzenie_watkow(pola, watki);
	/* ustawienie flagi zakończenia pracy, którą testują funkcje wątków
	   oraz odczyt ich bieżących liczników
	for (int i=0; i < 1; i++) {
		printf("wątek #%d\n",i);
	}
*/
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */
	return EXIT_SUCCESS;
}
//------------------------------------------------------------------------
