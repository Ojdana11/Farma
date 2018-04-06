#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "rysowanie.h"
#include "straznik.h"
#include "generator.h"

POLE pole[6];

#define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)
//pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[])
{
  if(!weryfikacja_argumentow(argc, argv)){
    return EXIT_FAILURE;
  }

  time_t tt;
  srand(time(&tt));
  int watki = atoi(argv[1]);
	int liczba_pol = atoi(argv[2]);
	int ch;

  /*Tworzenie okna, rysowanie pól*/
	initscr();
	start_color();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	init_pair(0, COLOR_BLUE, COLOR_CYAN);
  init_pair(1, COLOR_RED, COLOR_CYAN );
  init_pair(2, COLOR_GREEN, COLOR_CYAN );
  init_pair(3, COLOR_YELLOW, COLOR_CYAN );
  init_pair(4, COLOR_YELLOW, COLOR_CYAN );
  init_pair(5, COLOR_MAGENTA, COLOR_CYAN );
  init_pair(6, COLOR_BLUE, COLOR_CYAN );
  init_pair(7, COLOR_RED, COLOR_CYAN );

  init_pair(10, COLOR_CYAN, COLOR_BLACK );

	attron(COLOR_PAIR(10));
	printw("Press key down to exit");
	refresh();
	attroff(COLOR_PAIR(10));

  for(int i=0;i<liczba_pol;i++)
  {
    if(i>=3)
    {
      init_win_params(&pole[i], 1, i-3); //rysowanie.cpp
    }
    else{
      init_win_params(&pole[i], 0, i); //rysowanie.cpp
    }
    rysuj_pole(&pole[i], TRUE); //rysowanie.cpp
  }
//------------------------------------------------------------------------------------------

tworzenie_watkow(liczba_pol, watki); //generator.cpp
	while((ch = getch()) != KEY_DOWN)
	{
	}
	endwin();
	return 0;
}
