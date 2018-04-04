#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <ncurses.h>
#include "basic_objects.h"

#define liczba_pol 5;
  //int liczba_pol = sizeof(*pole) / sizeof(Pole);
pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

/* funkcja wykonywana w wątku - do głównego wątku ma zwracać położenie rolników*/
void* watek(void* _pole) {
  Pole *pole = (Pole*)_pole;
  int zebrane_plony =0;
  attron(A_BOLD);
  printw("Hello World !!!     ");	/* Print Hello World		  */
  printf("Watek %d\n", pthread_self());
  refresh();
  int nr_pola = rand()%liczba_pol;

  int count=0;

  while(count<20){
    nr_pola = rand()%liczba_pol;
    if(pole[nr_pola].wolne)
    {
      pole[nr_pola].wolne=false;
    //  	printf("Watek %d jest na polu nr: %d\n", pthread_self(), nr_pola);
      switch (pole[nr_pola].stan) {
        case orka:
        pole[nr_pola].stan = siew;
            usleep(1000);
        break;
        case siew:
        pole[nr_pola].stan = naworzenie;
            usleep(1000);
        break;
        case naworzenie:
        pole[nr_pola].stan = zbiory;
            usleep(1000);
        break;
        case zbiory:
        pole[nr_pola].stan = orka;
        zebrane_plony+=rand()%20;
            usleep(1000);
        break;
      }
  //    printf("Watek %d zwalnia pole nr: %d\n", pthread_self(), nr_pola);
      pole[nr_pola].wolne=true;
    }
    else{
    //  if(pole[nr_pola].do_zwolnienia<10)
      nr_pola = rand()%liczba_pol;
    }
    count++;
    usleep(10000);
  }
//  printf("Zebrane plony: %d \n", zebrane_plony);
	return NULL;
}
//------------------------------------------------------------------------
