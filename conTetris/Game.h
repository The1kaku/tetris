#include "Board.h"
#include "Piece.h"
#include <deque>

struct Game
{
	Game();
	Board board;
	std::deque< Piece> deque;
	Piece saved;
	unsigned long score;
	unsigned long lines;
	unsigned short level;

	int init();
	int loop();
	int exit();

	int newPiece();
	int handleInput();
};
