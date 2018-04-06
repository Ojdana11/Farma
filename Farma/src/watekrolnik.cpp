#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <ncurses.h>
#include "basic_objects.h"

extern int liczba_pol;
extern POLE pole[6];

void obrabianie_pola(POLE * pole, char znak, int nr_rolnika, char znak_rolnika){

  int i, j;
  	int x, y, w, h;
  	x = pole->startx;
  	y = pole->starty;
  	w = pole->szerokosc-1;
  	h = pole->wysokosc-1;
    mvaddch(y, x, znak_rolnika);
    refresh();
    for(j = y+1; j <= y + h; ++j){
      for(i = x+1; i <= x + w; ++i){
          mvaddch(j, i, znak);
          refresh();
          usleep(100000);
      }
    }
    refresh();

}

/* funkcja wykonywana w wątku - do głównego wątku ma zwracać położenie rolników*/
void* watek(void* _rolnik) {
  ROLNIK *rolnik = (ROLNIK*) _rolnik;
  int nr_pola, count=0;
  int nr_rolnika =rolnik->numer_rolnika;
  char znak_rolnika = rolnik->znak_rolnika;

  rolnik->gloway = rolnik->numer_rolnika*2 +3;
  rolnik->glowax = 4;

  while(count<4){
    nr_pola = rand()%liczba_pol;
    if(pole[nr_pola].wolne)
    {
      pole[nr_pola].wolne=false;
      rolnik->glowax=pole[nr_pola].startx;
      rolnik->gloway=pole[nr_pola].starty;

      switch (pole[nr_pola].stan) {
        case orka:
          pole[nr_pola].stan = siew;
          obrabianie_pola(&pole[nr_pola], '.',nr_rolnika, znak_rolnika);
          usleep(100000);
        break;
        case siew:
          pole[nr_pola].stan = naworzenie;
          obrabianie_pola(&pole[nr_pola], '#',nr_rolnika, znak_rolnika);
          usleep(100000);
        break;
        case naworzenie:
          pole[nr_pola].stan = zbiory;
          obrabianie_pola(&pole[nr_pola], 'x',nr_rolnika, znak_rolnika);
          usleep(100000);
          rolnik->zebrane_plony+=rand()%20;
        break;
        case zbiory:
        pole[nr_pola].stan = orka;
        obrabianie_pola(&pole[nr_pola], '~', nr_rolnika, znak_rolnika);
            usleep(100000);
        break;
      }
      mvprintw(rolnik->gloway, rolnik->glowax, "+");
      pole[nr_pola].wolne=true;
    }else{
    usleep(10000000);
    }
      count++;
  }
	return NULL;
}
//------------------------------------------------------------------------
