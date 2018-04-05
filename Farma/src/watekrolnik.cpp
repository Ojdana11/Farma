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

/* funkcja wykonywana w wątku - do głównego wątku ma zwracać położenie rolników*/
void* watek(void* _rolnik) {
  ROLNIK *rolnik = (ROLNIK*) _rolnik;

  int zebrane_plony =0;
  int pozycjay = pthread_self()%5 + rand()%10;
  int pozycjax = pozycjay+rand()%10;
  if( has_colors() == TRUE )
{
    start_color();
    init_pair( 2, COLOR_BLUE, COLOR_BLACK );
    attron( COLOR_PAIR( 2) );
    mvprintw(rolnik->numer_rolnika*2, 4, rolnik->znak);
    attroff( COLOR_PAIR(2)); //Wyłączenie koloru tekstu
}
	refresh();
  //printf("Watek %d\n", pthread_self()%100);
  int nr_pola = rand()%liczba_pol;

  int count=0;

  while(count<20){
    nr_pola = rand()%liczba_pol;
    if(pole[nr_pola].wolne)
    {
          //  printf("Watek %d ZAJMUJE pole nr: %d\n", pthread_self()%100, nr_pola);
      pole[nr_pola].wolne=false;
    //  	printf("Watek %d jest na polu nr: %d\n", pthread_self(), nr_pola);
      switch (pole[nr_pola].stan) {
        case orka:
        pole[nr_pola].stan = siew;
            //  printf("Watek %d sieje na polu nr: %d\n", pthread_self()%100, nr_pola);
            usleep(10000);
        break;
        case siew:
        pole[nr_pola].stan = naworzenie;
            //  printf("Watek %d nawozi pole nr: %d\n", pthread_self()%100, nr_pola);
            usleep(10000);
        break;
        case naworzenie:
        pole[nr_pola].stan = zbiory;
            //  printf("Watek %d kosi pole nr: %d\n", pthread_self()%100, nr_pola);
            usleep(10000);
                    zebrane_plony+=rand()%20;
        break;
        case zbiory:
        pole[nr_pola].stan = orka;
          //    printf("Watek %d orze pole nr: %d\n", pthread_self()%100, nr_pola);
            usleep(10000);
        break;
      }
    //  printf("Watek %d opuszcza pole nr: %d\n", pthread_self()%100, nr_pola);
      pole[nr_pola].wolne=true;
    }else{
  //    printf("Watek %d czeka ??? przy polu nr: %d\n", pthread_self()%100, nr_pola);
    }
    //  if(pole[nr_pola].do_zwolnienia<10)

    count++;
    usleep(100000);
  }
//  printf("Zebrane plony: %d \n", zebrane_plony);
	return NULL;
}
//------------------------------------------------------------------------
