#include "Display.h"
#include <curses.h>
#include <deque>

void addpiece(const Piece p)
{
	addpiece(p, p.coords.y, p.coords.x);
}

void addpiece(const Piece p, int y, int x)
{
	for (auto block : p.blocks)
	{
		move(y + block.y + 1, x + block.x + 1);
		attron(A_REVERSE);
		addch(' ');
		attroff(A_REVERSE);
	}
}

void adddeque(const std::deque<Piece> q)
{
	int y, x;
	y = -1;
	x = 12;
	for (auto it = q.begin(); ++it != q.end(); )
		addpiece(*it, (y += 3), x);
}

void addboard(const Board b)
{
	move(1, 0);
	for (auto row : b.stack)
	{
		addch(' ');
		for (auto i : row)
			if (i)
			{
				attron(A_REVERSE);
				addch(' ');
				attroff(A_REVERSE);
			}
			else
			{
				addch('.');
			}
		addch('\n');
	}
}

void addscore(unsigned long score, unsigned long lines, unsigned short level)
{
	move(0, 0);
	printw("SCORE:%d\tLINES:%d\tLEVEL:%d", score, lines, level);
}
