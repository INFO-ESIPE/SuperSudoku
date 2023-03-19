#ifndef _INTERFACE_
#define _INTERFACE_

#include "sudoku.h"

#define HEIGHT_WINDOWS_PIX 600
#define WIDTH_WINDOWS_PIX 800

#define WAIT_TIME_MILLISEC 500

void create_windows(void);
void free_windows(void);
void actualise_window(void);
void clear_window(void);
void wait_window(int sec);
void print_grid(Board grid, Board exemple);
void resolve_sudoku(Board grid, Board exemple);
void print_numbers(void);
void wait_number(int x, int y, Board grid);
void color_case(int x, int y);
void game_completed(void);
void quit_game(int width, int height, int x, int y);

#endif