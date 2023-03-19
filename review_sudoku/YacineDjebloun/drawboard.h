#ifndef __drawboard__
#define __drawboard__

#include "sudoku.h"

int drawBoard(int square_count, int square_dim, int cell_size, Board grid);
int drawSquareCenter(int sqr, int cell_size, int square_dim);
int drawChoicesBoard(int square_count, int square_dim, int cell_size, Board grid);
int getCenterCoord(int sqr, int cell_size, int square_dim);
int drawChoicesSquare(int x, int y, int cell_size, int square_dim);

#endif
