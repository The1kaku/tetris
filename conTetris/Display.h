#ifndef DISPLAY_H
#define DISPLAY_H
#include "Piece.h"
#include "Board.h"
#include <deque>

void addpiece(const Piece p);
void addpiece(const Piece p, int y, int x);
void addboard(const Board b);
void adddeque(const std::deque<Piece> q);
void addscore(unsigned long score, unsigned long lines, unsigned short level);
#endif
