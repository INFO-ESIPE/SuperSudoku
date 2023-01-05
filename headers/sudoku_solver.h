/*
	Programmation C - TP7
	Max Ducoudré - INFO1
    Fonctions permettant de gérer le solveur de la grille de sudoku
*/

#ifndef _SUDOKUSOLVER_
#define _SUDOKUSOLVER_

#include "constants.h"
#include "grid_utility.h"

int resolveGrid(struct SuperSudoku grids, int x, int y);
int can_play_value(struct SuperSudoku grids, int x, int y, int value);
int gridOffset2D(int x, int y);

#endif