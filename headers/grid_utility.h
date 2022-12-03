#ifndef _GRIDUTILITY_
#define _GRIDUTILITY_


typedef int* SudokuGrid; /* Une grille est un tableau d'entier de 9x9 */

/* Structure comportant les élements pour le bon déroulement du jeu*/
struct SuperSudoku {
  SudokuGrid gameGrid; /* Contient la grille actuelle du sudoku avec les valeurs*/           
  SudokuGrid forbiddenGrid; /* Contient les endroits où il est impossible de jouer (les valeurs par défaut à la génération de la grille)*/
}; 


int gridOffset(int x1, int y1, int x2, int y2);
int isSlotCompatibleInGrid(SudokuGrid grid, int x1, int y1, int x2, int y2, int value);
int playOnGrid(struct SuperSudoku grids, int x1, int y1, int x2, int y2, int value);

#endif