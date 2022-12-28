/*
	Programmation C - TP7
	Max Ducoudré - INFO1
  Fonctions permettant de gérer le clique et la position de la souris lors de la partie
*/

#ifndef _MOUSELISTENER_
#define _MOUSELISTENER_


#include "grid_frame.h"
#include "grid_utility.h"

/*Bibliothèque graphique*/
#include <MLV/MLV_all.h>

/*Permet de gérer le bouton pour résoudre le sudoku*/
#include "sudoku_solver.h"

/*Pour terminer le programme (SIGKILL)*/
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

struct SelectorSlotLocation {
  int x;
  int y; 
};

struct MenuButton;


void* mouseClick(void* args);
void mouseOver(void *args);
void startListenMouse(struct SuperSudoku grids);
void freeListener();

void emptyCurrentSelectedSlot();
int slotIsEmpty(struct SlotLocation slotLocation);
struct SlotLocation getCurrentSelectedSlot();

int getCurrentOverSelectorSlot();
int getCurrentOverSlotLocation(struct SlotLocation *overSlotLocation);

int listen_button(int mouseX, int mouseY, struct MenuButton button);

#endif
