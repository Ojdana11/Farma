#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <ncurses.h>
#include <math.h>
#include "basic_objects.h"

extern int liczba_pol;
extern POLE pole[6];

void obrabianie_pola(POLE * pole, char znak, int nr_rolnika, char znak_rolnika){

  int i, j;
  	int x, y, w, h, nornice,ile_extra;
    ile_extra = (rand()%5)*(pow(-1,rand()%6));
    nornice = ile_extra*10000;
    pole->do_zwolnienia =100;
  	x = pole->startx;
  	y = pole->starty;
  	w = pole->szerokosc-1;
  	h = pole->wysokosc-1;
    mvaddch(y, x, znak_rolnika);
    refresh();
    if(nornice>0)
    {
      mvhline(pole->starty-1, pole->startx+4, '-', abs(ile_extra));
    }
    if(nornice<0)
    {
      mvhline(pole->starty-1, pole->startx+4, '+', abs(ile_extra));
    }
    for(j = y+1; j <= y + h; ++j){
      for(i = x+1; i <= x + w; ++i){
          mvaddch(j, i, znak);
          pole->do_zwolnienia--;
          refresh();
          usleep(100000+nornice);
      }
    }
    mvprintw(y, x, "+");
        mvprintw(pole->starty-1,pole->startx+4,"%s","            ");
    pole->wolne=true;
    pole->do_zwolnienia =0;
    refresh();

}

void wybor_pracy(POLE * pole, ROLNIK * rolnik){

  rolnik->glowax=pole->startx;
  rolnik->gloway=pole->starty;

  switch (pole->stan) {
    case orka:
      pole->stan = siew;
      obrabianie_pola(pole, '.',rolnik->numer_rolnika, rolnik->znak_rolnika);
      usleep(100000);
    break;
    case siew:
      pole->stan = naworzenie;
      obrabianie_pola(pole, '#',rolnik->numer_rolnika, rolnik->znak_rolnika);
      usleep(100000);
    break;
    case naworzenie:
      pole->stan = zbiory;
      obrabianie_pola(pole, 'x',rolnik->numer_rolnika, rolnik->znak_rolnika);
      usleep(100000);
      rolnik->zebrane_plony+=rand()%20;
    break;

    case zbiory:
      pole->stan = orka;
      obrabianie_pola(pole, '~', rolnik->numer_rolnika, rolnik->znak_rolnika);
      usleep(100000);
    break;
  }
}
/* funkcja wykonywana w wątku - do głównego wątku ma zwracać położenie rolników*/
void* watek(void* _rolnik) {
  ROLNIK *rolnik = (ROLNIK*) _rolnik;
  int nr_pola;
  char znak_rolnika = rolnik->znak_rolnika;

  //rolnik->gloway = rolnik->numer_rolnika*2 +3;
  //rolnik->glowax = 4;

  while(rolnik->zebrane_plony<20){
    nr_pola = rand()%liczba_pol;
    if(pole[nr_pola].wolne)
    {
      pole[nr_pola].wolne=false;
      wybor_pracy(&pole[nr_pola], rolnik);


    }else{
      if(pole[nr_pola].do_zwolnienia<20)
      {
        mvaddch(pole[nr_pola].starty-1, pole[nr_pola].startx+1, znak_rolnika);
        mvaddch(pole[nr_pola].starty-1, pole[nr_pola].startx+2, '?');
        refresh();
        while(pole[nr_pola].wolne==false){
        }
        pole[nr_pola].wolne=false;
        mvaddch(pole[nr_pola].starty-1, pole[nr_pola].startx+4, ' ');
        mvaddch(pole[nr_pola].starty-1, pole[nr_pola].startx+5, ' ');
        refresh();
        wybor_pracy(&pole[nr_pola], rolnik);

      }
    //usleep(10000000);
    }
  }
	return NULL;
}
//------------------------------------------------------------------------
