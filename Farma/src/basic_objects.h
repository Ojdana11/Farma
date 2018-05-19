#include <string>

enum Stan {orka, siew, naworzenie, zbiory};

typedef struct _win_border_struct {

	chtype 	ls, rs, ts, bs,
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct _POLE_struct{

  bool wolne;
  Stan stan;
  int do_zwolnienia;
  int startx, starty;
  int wysokosc, szerokosc;
  WIN_BORDER border;
} POLE;

typedef struct _ROLNIK_struct{
	int glowax,gloway;
	char znak_rolnika;
	int numer_rolnika;
	chtype kolor;
	char znak[2];
	int zebrane_plony;
	int liczba_zbiorow;
} ROLNIK;
