/*
	Programmation C - TP7
	Max Ducoudré - INFO1
    Fonctions permettant de gérer la grille
*/

#ifndef _GRIDUTILITY_
#define _GRIDUTILITY_


/* Permet de gérer le timer */
#include "timer.h"

#include "constants.h"

typedef int* SudokuGrid; /* Une grille est un tableau d'entier de 9x9 */

/* Structure comportant les élements pour le bon déroulement du jeu*/
struct SuperSudoku {
  SudokuGrid gameGrid; /* Contient la grille actuelle du sudoku avec les valeurs*/           
  SudokuGrid forbiddenGrid; /* Contient les endroits où il est impossible de jouer (les valeurs par défaut à la génération de la grille)*/
}; 

struct SlotLocation {
  int x1; /* Position x de la cellule 3x3*/
  int y1; /* Position y de la cellule 3x3*/
  int x2; /* Position x de la case dans la cellule*/
  int y2; /* Position y de la case dans la cellule*/
};

struct Timer {
  int minutes;
  int seconds;
  int milliseconds;
};

int gridOffset(int x1, int y1, int x2, int y2);

void getTimerString(char* buffer);
void consolePrintMainGrid(SudokuGrid grid);

int isGridCorrect(SudokuGrid gameGrid);
int isGridFull(SudokuGrid gameGrid);

int isSlotCompatibleInGrid(SudokuGrid grid, int x1, int y1, int x2, int y2, int value);
int playOnGrid(SudokuGrid gameGrid, SudokuGrid forbiddenGrid, int x1, int y1, int x2, int y2, int value);


void startGame();
void endGame(int registerScore);
void restartGame(struct SuperSudoku oldGrid);

#endif