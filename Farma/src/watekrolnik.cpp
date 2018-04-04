#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include "basic_objects.h"

/* funkcja wykonywana w wątku - zwiększa licznik */
void* watek(void* _pole) {
	Pole *pole = (Pole*)_pole;
	printf("Watek %d\n", pole[0].do_zwolnienia);
	usleep(1);

	return NULL;
}
//------------------------------------------------------------------------
