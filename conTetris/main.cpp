#include "Game.h"
#include <curses.h>

int main()
{
	initscr();
	while (true)
	{
		printw("Play Game (1)\nControls (2)\nExit (3)\n\n\nPlease type number to selection option");
		int c = getch();
		if ( c == '1')
		{
				clear();
				endwin();
				Game game;
		}
		else if (c == '2')
		{
				clear();
				printw("q / f to rotate\na / s to move horisontally\nr to send down fast\nw to save or swap with saved\nUppercase will repeat command until it stops working (nothing for w)\ne / E to exit");
				printw("=\n\n\n\n\t\tPress any key to go back");
				getch();
		}
		else if (c == '3')
		{
			endwin();
			return 0;
		}
				clear();
	}
}
