#ifndef __SUDOKU__
#define __SUDOKU__

typedef int Board[9][9];

void initialize_empty_board(Board grid);
void print_board(Board grid);
int *create_array();
int is_value_correct(Board grid, int ligne, int colonne, int value);
int is_grid_correct(Board grid);

#endif
