/*
	Programmation C - TP7
	Max Ducoudré - INFO1
    Fonctions permettant de gérer la partie graphique de la grille
*/

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


/*Couleurs MLV*/
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
#define WAIT_TIME_MILLISEC 13

/*Permet de stocker les données d'un bouton*/
struct MenuButton {
    int x;
    int y;
    int width;
    int height;
    MLV_Color color;
    MLV_Color over_color;
    char* text;
    MLV_Font* font;
};

/*Ouverture et fermeture de la fenêtre graphique*/
void generateGridFrame(struct SuperSudoku grids);
void freeFrame();

/*Fonctions permettant de faire le dessin sufr la fenêtre*/
void startDrawUpdate(struct SuperSudoku grids);
int updateDraw(struct SuperSudoku grids);
void drawMainGrid(struct SuperSudoku grids);

/*Fonctions permettant de récupérer des informations depuis la fenêtre graphique*/
int getSlotFromCoordinates(int x, int y, struct SlotLocation *slot);
int getSlotChoice(int mouseX, int mouseY, int* selected_value);
int getCurrentAction();

/*Fonctions permettant de gérer les boutons*/
void drawButton(struct MenuButton menuButton);
struct MenuButton getMenuButtons(int button_id);
void setDrawScore(int rawScoresStatus);

#endif