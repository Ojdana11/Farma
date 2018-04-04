#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include "rysowanie.h"


//jako argumenty przekazywane będą wartości pola oraz położenia rolników
int main(int argc, char *argv[])
{
  int liczba_pol = 3;//atoi(argv[1]);
  WIN win1,win2, win3;
	int ch;

	initscr();			/* Start curses mode 		*/
	start_color();			/* Start the color functionality */
	cbreak();			/* Line buffering disabled, Pass on
					 * everty thing to me 		*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
	noecho();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);

	/* Initialize the window parameters */
//  for(int i=0;i<liczba_pol;i++)
//  {
	init_win_params(&win1, 0);
  	init_win_params(&win2, 1);
    	init_win_params(&win3, 2);
	print_win_params(&win2);
  	print_win_params(&win3);
    	print_win_params(&win1);
//}
	attron(COLOR_PAIR(1));
	printw("Press F1 to exit");
	refresh();
	attroff(COLOR_PAIR(1));

//for(int i=0;i<liczba_pol;i++)
{
	rysuj_pole(&win1, TRUE);
  rysuj_pole(&win2, TRUE);
  rysuj_pole(&win3, TRUE);
}

	while((ch = getch()) != KEY_F(1))
	{	/*switch(ch)
		{	case KEY_LEFT:
				//rysuj_pole(&win, FALSE);
				//--win.startx;
				rysuj_pole(&win[0], TRUE);
				break;
			case KEY_RIGHT:
				rysuj_pole(&win[0], FALSE);
				++win.startx;
				rysuj_pole(&win[0], TRUE);
				break;
			case KEY_UP:
				rysuj_pole(&win[0], FALSE);
				--win.starty;
				rysuj_pole(&win, TRUE);
				break;
			case KEY_DOWN:
				rysuj_pole(&win, FALSE);
				++win.starty;
				rysuj_pole(&win, TRUE);
				break;
		}*/
	}
	endwin();			/* End curses mode		  */
	return 0;
}
