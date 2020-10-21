#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Piece.h"

struct Piece;

struct Board
{
	Board();
	std::array< std::array< bool, 10>, 20> stack;

	bool get(int y, int x) const { return stack[y][x]; }
	void set(int y, int x) { stack[y][x] = true; }
	void set(Piece p);
	std::array< std::array< bool, 10>, 20>::reverse_iterator delRow(std::array< std::array< bool, 10>, 20>::reverse_iterator row); 
};
bool isRowEmpty(std::array< bool, 10> *row);
bool isRowFilled(std::array< bool, 10> *row);
#endif
