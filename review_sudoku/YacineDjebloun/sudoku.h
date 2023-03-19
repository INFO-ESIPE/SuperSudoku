#ifndef __SUDOKU__
#define __SUDOKU__

typedef int Board[9][9];

void print_board(Board grid);
int is_full_grid(Board grid);
void solver(Board grid);
int contraintes(Board grid, int i, int j, int number);
int initialise_grid_choice(Board choice);


#endif