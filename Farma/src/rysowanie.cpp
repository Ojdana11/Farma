#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include "basic_objects.h"

void init_win_params(WIN *p_win, int nr_pola)
{
	p_win->wysokosc = 6;
	p_win->szerokosc = 15;

	p_win->starty = (nr_pola*8+1);
	p_win->startx = (nr_pola*20+5);


	p_win->border.ls = '|';
	p_win->border.rs = '|';
	p_win->border.ts = '-';
	p_win->border.bs = '-';
	p_win->border.tl = '+';
	p_win->border.tr = '+';
	p_win->border.bl = '+';
	p_win->border.br = '+';

}
void print_win_params(WIN *p_win)
{
#ifdef _DEBUG
	mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty,
				p_win->szerokosc, p_win->wysokosc);
	refresh();
#endif
}
void rysuj_pole(WIN *p_win, bool flag)
{	int i, j;
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->szerokosc;
	h = p_win->wysokosc;

	if(flag == TRUE)
	{	mvaddch(y, x, p_win->border.tl); //lewy górny
		mvaddch(y, x + w, p_win->border.tr); //prawy górny
		mvaddch(y + h, x, p_win->border.bl); //lewy dolny
		mvaddch(y + h, x + w, p_win->border.br); //prawy dolny
		mvhline(y, x + 1, p_win->border.ts, w - 1); //góra
		mvhline(y + h, x + 1, p_win->border.bs, w - 1); //dół
		mvvline(y + 1, x, p_win->border.ls, h - 1); //lewa
		mvvline(y + 1, x + w, p_win->border.rs, h - 1); //prawa
    for(j=1;j<h;j++)
      mvhline(y+j, x + 1, 'x', w - 1); //góra

	}
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');

	refresh();

}
