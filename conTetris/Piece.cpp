#include "Piece.h"

Piece::Piece(int type) : coords(1, 5)
{
	switch(type)
	{
	case 'i': case 'I': case 1:
		this->blocks[0].y = 0;
		this->blocks[0].x = 0;
		this->blocks[1].y = 0;
		this->blocks[1].x = 1;
		this->blocks[2].y = 0;
		this->blocks[2].x = 2;
		this->blocks[3].y = 0;
		this->blocks[3].x = -1;
		break;
	case 'j': case 'J': case 2:
		this->blocks[0].y = 0;
		this->blocks[0].x = 0;
		this->blocks[1].y = 0;
		this->blocks[1].x = 1;
		this->blocks[2].y = 0;
		this->blocks[2].x = -1;
		this->blocks[3].y = -1;
		this->blocks[3].x = -1;
		break;
	case 'l': case 'L': case 3:
		this->blocks[0].y = 0;
		this->blocks[0].x = 0;
		this->blocks[1].y = 0;
		this->blocks[1].x = 1;
		this->blocks[2].y = -1;
		this->blocks[2].x = 1;
		this->blocks[3].y = 0;
		this->blocks[3].x = -1;
		break;
	case 'o': case 'O': case 4:
		this->blocks[0].y = 0;
		this->blocks[0].x = 0;
		this->blocks[1].y = 0;
		this->blocks[1].x = 1;
		this->blocks[2].y = -1;
		this->blocks[2].x = 1;
		this->blocks[3].y = -1;
		this->blocks[3].x = 0;
		break;
	case 's': case 'S': case 5:
		this->blocks[0].y = 0;
		this->blocks[0].x = 0;
		this->blocks[1].y = -1;
		this->blocks[1].x = 1;
		this->blocks[2].y = -1;
		this->blocks[2].x = 0;
		this->blocks[3].y = 0;
		this->blocks[3].x = -1;
		break;
	case 't': case 'T': case 6:
		this->blocks[0].y = 0;
		this->blocks[0].x = 0;
		this->blocks[1].y = -1;
		this->blocks[1].x = 0;
		this->blocks[2].y = 0;
		this->blocks[2].x = 1;
		this->blocks[3].y = 0;
		this->blocks[3].x = -1;
		break;
	case 'z': case 'Z': case 7:
		this->blocks[0].y = 0;
		this->blocks[0].x = 0;
		this->blocks[1].y = -1;
		this->blocks[1].x = -1;
		this->blocks[2].y = -1;
		this->blocks[2].x = 0;
		this->blocks[3].y = 0;
		this->blocks[3].x = 1;
		break;
	default:
		this->coords.y = 0;
		this->coords.x = 0;
		break;
	}
}

bool translate(Piece *piece, const Board *board, int dy, int dx)
{
	Piece copy = *piece;
	copy.coords.y += dy;
	copy.coords.x += dx;

	if (copy.coords.y < 0 || copy.coords.x < 0 || copy.coords.y >= 20 || copy.coords.x >= 10)
		return false;

	for(auto block : copy.blocks)
		if (copy.coords.y + block.y < 0 || copy.coords.x + block.x < 0 || copy.coords.y + block.y >= 20 || copy.coords.x + block.x >= 10 || board->get(copy.coords.y + block.y, copy.coords.x + block.x))
				return false;
	
	*piece = copy;
	return true;
}

bool rotate(Piece *piece, const Board *board, int dir)
{
	Piece copy = *piece;

	int m0, m2;
	if (dir >= 0)
	{
		m0 = 1;
		m2 = -1;
	}
	else 
	{
		m0 = -1;
		m2 = 1;
	}	

	for (auto &block : copy.blocks)
	{
		int newX = block.y * m0;
		int newY = block.x * m2;
		block.y = newY;
		block.x = newX;

		if (copy.coords.y + block.y < 0 || copy.coords.x + block.x < 0 || copy.coords.y + block.y >= 20 || copy.coords.x + block.x >= 10 || board->get(copy.coords.y + block.y, copy.coords.x + block.x))
				return false;
	}

	*piece = copy;
	return true;
}
