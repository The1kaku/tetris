#include "Game.h"
#include <chrono>
#include <Windows.h>
#include "Display.h"
#include <curses.h>
#define TARGET_FPS 120 
#define FRAME_TIME 1000 / TARGET_FPS

double ms;

struct Timer
{
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::duration<double> duration;

	Timer() 
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		duration = std::chrono::high_resolution_clock::now() - start;
		ms = duration.count() * 1000.0f;
	}
};

Game::Game() : score(0), lines(0), saved(-1)
{
	if (init())
		while (loop())
			Sleep(ms + FRAME_TIME);
	exit();
}

int Game::init()
{
	for (int i = 0; i < 7; ++i)
		this->deque.emplace_back(newPiece());

	initscr();
	noecho();
	nodelay(stdscr, true);
	keypad(stdscr, true);

	srand(time(0));
	return 1;
}

int Game::exit()
{
	clear();
	nodelay(stdscr, false);
	printw("You Lost!\n\n\nSCORE:%d\nLINES:%d\nLEVEL:%d", score, lines, level);
	printw("\n\n\n\npress SPACE to exit!");
	while (getch() != ' ');
	endwin();
	return 1;
}

int Game::loop()
{
	static double tickrate = 500.0;
	static double timing = 0.0;
	Timer timer;
	level = score / 1000;
	tickrate = 500.0 - level * 20;
	if (!isRowEmpty(&board.stack[1]))
		return 0;
	if (!handleInput())
		return 0;
	clear();
	addboard(board);
	addpiece(deque.front());
	addscore(score, lines, level);
	adddeque(deque);
	if (saved.coords.y != 0 && saved.coords.x != 0)
		addpiece(saved, 2, 16);
	if (timing > tickrate)
	{
		timing = 0.0;
		if (!translate(&deque.front(), &board, 1, 0))
		{
			board.set(deque.front());
			deque.pop_front();
			deque.emplace_back(newPiece());
		}
	}
	refresh();

	int lines = 0;
	move(0, 20);
	for (auto row = board.stack.rbegin(); row != board.stack.rend(); ++row)
		if (isRowFilled(&*row))
		{
			++lines;
			row = board.delRow(row);
		}
	this->lines += lines;
	switch (lines)
	{
	case 0:
		break;
	case 1: case 2:
		score += lines * 100;
		break;
	case 3:
		score += 500;
		break;
	case 4:
		score += 2500;
		break;
	default:
		break;
	}

	timing += FRAME_TIME;
	return 1;
}

int Game::newPiece()
{
	return rand() % 7 + 1;
}

int Game::handleInput()
{
	int in = getch();

	switch (in)
	{
		case 'a':
			translate(&deque.front(), &board, 0, -1);
			return 1;
		case 'A':
			while (translate(&deque.front(), &board, 0, -1));
			return 1;
		case 's':
			translate(&deque.front(), &board, 0, 1);
			return 1;
		case 'S':
			while (translate(&deque.front(), &board, 0, 1));
			return 1;
		case 'q': case 'Q':
			rotate(&deque.front(), &board, 1);
			return 1;
		case 'f': case 'F':
			rotate(&deque.front(), &board, -1);
			return 1;
		case 'r': 
			translate(&deque.front(), &board, 1, 0);
			return 1;
		case 'R':
			while (translate(&deque.front(), &board, 1, 0));
			score += 25 * level;
			return 1;
		case 'w': case 'W':
			if (saved.coords.y == 0 && saved.coords.x == 0)
			{
				saved = deque.front();
				deque.pop_front();
				deque.emplace_back(newPiece());
			}
			else if (deque.front().coords.y < 3)
			{
				Piece temp = deque.front();
				deque.front() = saved;
				saved = temp;
				saved.coords.y = 1;
				saved.coords.x = 5;
			}
			return 1;
		case 'e': case 'E':
			return 0;
		default:
			return 1;
	}
}
