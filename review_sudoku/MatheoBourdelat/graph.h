#ifndef GRAPH_H
#define GRAPH_H

#include "sudoku.h"

#define WIN_HEIGHT 1000
#define WIN_WIDTH 1000
#define MARGE 50
#define TAILLE_CASE 70

int generate_frame(Board board);
int draw_grille(Board board);
int listen_mouse(Board board);
int pix_to_game(int x, int y, int* i, int* j);
int draw_tab(Board Board);
int pix_to_select(int x, int y, int* k);
int validation(Board board, int ligne, int colonne, int j);

#endif