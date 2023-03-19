#ifndef __mouse__
#define __mouse__

#include "sudoku.h"

int isClickInGrid(int x, int y, int cell_size, int square_dim, int square_count);
int isInEmptySquare(int x, int y, int cell_size, int square_dim, int square_count, Board grid);
int isInChoiceGrid(int x, int y, int cell_size, int square_dim, int square_count);
int updateGrid(int x, int y, int old_x, int old_y, int cell_size, int square_dim, int square_count, Board grid, Board Choice);
#endif
