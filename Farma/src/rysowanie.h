#ifndef RYSOWANIE_H
#define RYSOWANIE_H

#include "basic_objects.h"

  void init_win_params(POLE *p_win, int nr_polax, int nr_polay);
  void print_win_params(POLE *p_win);
  void rysuj_pole(POLE *win, bool flag);

#endif
