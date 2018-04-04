enum Stan {orka, siew, naworzenie, zbiory};

struct Pole{
  bool wolne;
  Stan stan;
  int do_zwolnienia;
};

typedef struct _win_border_struct {
	chtype 	ls, rs, ts, bs,
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {

	int startx, starty;
	int wysokosc, szerokosc;
	WIN_BORDER border;
}WIN;
