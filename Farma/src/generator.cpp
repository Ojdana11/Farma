#define _XOPEN_SOURCE	500
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include "basic_objects.h"
#include "watekrolnik.h"
#include <ncurses.h>

#define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)

void tworzenie_watkow(int pola, int watki){

    pthread_t id_watek[watki];
    Pole pole[pola];
	  pthread_attr_t attr;
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
    printf("Tworze watki\n");
    /* utworzenie kilku wątków wątku z różnymi priorytetami */
	  for (int i=0; i < watki; i++) {
		     /* kolejne wątki mają coraz wyższe priorytety */
		  sp.sched_priority = pmin + (pmax-pmin) * i/(float)(watki-1);

      //Rysowanie pola

      pole[i].wolne   =   true;
		  pole[i].stan    =   orka;
		  pole[i].do_zwolnienia = 0;

		  /* ustawienie priorytetu */
		  errno = pthread_attr_setschedparam(&attr, &sp);
		  test_errno("pthread_attr_setschedparam");

		  /* uruchomienie wątku */
		  errno = pthread_create(&id_watek[i], &attr, watek, pole);
		  test_errno("pthread_create");

	 }

  /*niszczenie zmiennej atrybut wątków*/
  errno = pthread_attr_destroy(&attr);
	test_errno("pthread_attr_destroy");

  /* teraz oczekiwanie na ich zakończenie */
  for (int i=0; i < watki; i++) {
    errno = pthread_join(id_watek[i], NULL);
    test_errno("pthread_join");
  }
}
