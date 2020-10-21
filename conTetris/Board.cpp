#include "Board.h"

Board::Board()
{
	for (int i = 0; i < 20; ++i)
		for (int j = 0; j < 10; ++j)
			this->stack[i][j] = false;
}

bool isRowEmpty(std::array< bool, 10> *row)
{
	std::array< bool, 10>::const_iterator end = row->cend();
	std::array< bool, 10>::const_iterator begin = row->cbegin();
	while (begin != end)
		if (*begin++)
			return false;
	return true;
}

bool isRowFilled(std::array< bool, 10> *row)
{
	std::array< bool, 10>::const_iterator end = row->cend();
	std::array< bool, 10>::const_iterator begin = row->cbegin();
	while (begin != end)
		if (!*begin++)
			return false;

	return true;
}

std::array< std::array< bool, 10>, 20>::reverse_iterator Board::delRow(std::array< std::array< bool, 10>, 20>::reverse_iterator row)
{
	std::array< std::array< bool, 10>, 20>::reverse_iterator nextRow = row;
	std::array< std::array< bool, 10>, 20>::reverse_iterator next = row;
	nextRow++;
	while (nextRow != stack.rend())
		*(row++) = *(nextRow++);
	return --next;
}

void Board::set(Piece p)
{
	for (auto block : p.blocks)
		stack[p.coords.y + block.y][p.coords.x + block.x] = true;
}
