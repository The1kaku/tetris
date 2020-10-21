#ifndef PIECE_H
#define PIECE_H

#include <array>
#include "Board.h"

struct Board;

struct Point
{
	Point(int y, int x) : y(y), x(x) { } 
	Point() : Point(0, 0) { }
	int y, x;
};

struct Piece
{
	Piece(int type);

	Point coords;
	std::array< Point, 4> blocks;

};

bool translate(Piece *piece, const Board *board, int dy, int dx);
bool rotate(Piece *piece, const Board *board, int dir); // Positive is clockwise, negative is counter clockwise
#endif
