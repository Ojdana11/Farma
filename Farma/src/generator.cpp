#define _XOPEN_SOURCE	500
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <string>
#include "basic_objects.h"
#include "watekrolnik.h"

#define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)
int liczba_pol;
extern POLE pole[6];

void tworzenie_watkow(int pola, int watki){

    pthread_t id_watek[watki];
	  pthread_attr_t attr;
    ROLNIK rolnik[watki];
    liczba_pol = pola;
    int pmin, pmax;
    int sched_policy;
    struct sched_param sp;
    sched_policy = SCHED_OTHER; //SCHED_RR, SCHED_FIFO, SCHED_OTHER

    pmin = sched_get_priority_min(sched_policy);
  	pmax = sched_get_priority_max(sched_policy);

  	errno = pthread_attr_init(&attr);
  	test_errno("pthread_attr_init");

  	/* parametry szeregowania odczytywane z atrybutów  */
  	errno = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
  	test_errno("pthread_attr_setinheritsched");

  	/* wybór podanego algorytmu szeregowania */
  	errno = pthread_attr_setschedpolicy(&attr, sched_policy);
  	test_errno("pthread_attr_setschedpolicy");

    for(int i=0; i<pola; i++)
    {
      pole[i].wolne   =   true;
      pole[i].stan    =   orka;
      pole[i].do_zwolnienia = 0;
    }

    /* utworzenie kilku wątków wątku z różnymi priorytetami */
	  for (int i=0; i < watki; i++) {
		     /* kolejne wątki mają coraz wyższe priorytety */
		  sp.sched_priority = pmin + (pmax-pmin) * i/(float)(watki-1);

		  /* ustawienie priorytetu */
		  errno = pthread_attr_setschedparam(&attr, &sp);
		  test_errno("pthread_attr_setschedparam");
      rolnik[i].numer_rolnika = i;
      rolnik[i].znak_rolnika = 'A'+i;
      rolnik[i].zebrane_plony =0;
      rolnik[i].liczba_zbiorow=0;
      //printf("%d\n",rolnik.numer_rolnika);
		  /* uruchomienie wątku */
		  errno = pthread_create(&id_watek[i], &attr, watek, &rolnik[i]);
		  test_errno("pthread_create");

	 }
   int kolumny = 0;
   int rzedy = 0;
   getmaxyx( stdscr, rzedy, kolumny );
   mvprintw(10,kolumny/2,"%s","Rolnik      zebrane plony      liczba zbiorow");
   char ch;
//(ch = getch()) != KEY_DOWN
   while((ch = getch()) != 'q')
   {
     for(int i=0;i<watki;i++)
     {
       mvaddch(12+i,kolumny/2+2,rolnik[i].znak_rolnika);
       mvprintw(12+i,kolumny/2+18,"%d",rolnik[i].zebrane_plony);
       mvprintw(12+i,kolumny/2+36,"%d",rolnik[i].liczba_zbiorow);
       refresh();
     }
        //  return ;
   }
 return ;

   /*niszczenie zmiennej atrybut wątków*/
   errno = pthread_attr_destroy(&attr);
 	test_errno("pthread_attr_destroy");

   /* teraz oczekiwanie na ich zakończenie */
   for (int i=0; i < watki; i++) {
     errno = pthread_join(id_watek[i], NULL);
     test_errno("pthread_join");
   }



}
