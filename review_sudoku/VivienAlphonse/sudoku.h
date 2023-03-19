#ifndef SUDOKU_H
#define SUDOKU_H

#include "interface.h"

int playCase(Board *current_board, struct Grid_properties grid, int grid_line, int grid_column, int show_right_answers);
int *find_already_used_values(Board current_board, int grid_line, int grid_column, int grid_size);
int is_board_full(Board board, int grid_size);

#endif /* SUDOKU_H */