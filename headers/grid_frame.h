#ifndef _GRIDFRAME_
#define _GRIDFRAME_

/* utilisé pour lire les données de la grille */
#include "../headers/grid_utility.h"
#include "../headers/constants.h"

/*Permet de gérer la souris*/
#include "../headers/mouse_listener.h"

/*Bibliothèque graphique*/
#include <MLV/MLV_all.h>

/* Thread pour actualiser l'affichage*/
#include <pthread.h>

/* Constantes graphique */
#define GAME_NAME "SuperSudoku"
#define WIN_WIDTH 1000
#define WIN_HEIGHT 650

#define GRID_WIDTH 600
#define GRID_HEIGHT 650

#define MARGIN_LEFT WIN_WIDTH/20
#define MARGIN_TOP WIN_HEIGHT/10

#define SLOT_SIZE GRID_WIDTH/10


#define WHITE MLV_rgba(255,255,255,255)
#define BLACK MLV_rgba(0,0,0,255)
#define GRAY MLV_rgba(128,128,128,255)
#define ORANGE MLV_rgba(255,165,0,255)

#define GREEN MLV_rgba(0,255,0,255)
#define RED MLV_rgba(255,0,0,255)


/* User action*/
#define ACTION_RESTART_PARTY 2
#define ACTION_END_PARTY 1
#define ACTION_EMPTY 0
#define ACTION_END -1
#define WAIT_TIME_MILLISEC 500


void generateGridFrame(struct SuperSudoku grids);
void startDrawUpdate(struct SuperSudoku grids);
void* updateDraw(void* arg);
int getSlotFromCoordinates(int x, int y, struct SlotLocation *slot);
void drawMainGrid(struct SuperSudoku grids);
int getSlotChoice(int mouseX, int mouseY, int* selected_value);
void freeFrame();
int getCurrentAction();

#endif