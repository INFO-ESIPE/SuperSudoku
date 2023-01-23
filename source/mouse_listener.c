/*
	Programmation C - TP7
	Max Ducoudré - INFO1
    Fonctions permettant de gérer le clique et la position de la souris lors de la partie
*/

#include <stdio.h>
#include <stdlib.h>

#include "../headers/mouse_listener.h"

struct SlotLocation currentSelectedSlot = {-1,-1,-1,-1}; /*Variable contenant la case séléctionnée*/
struct SuperSudoku grids;

/* Fonction permettant d'activer l'écoute de la souris avec un thread*/
void startListenMouse(struct SuperSudoku superGrids)
{
    pthread_t threadMouseID;
    grids = superGrids;
    pthread_create(&threadMouseID, NULL, &mouseClick, &grids);
}


/* Fonction permettant de gérer le survol de la souris*/
void mouseOver(void *args)
{
    
    int mouseX;
    int mouseY;
    while(0 && getCurrentAction() != ACTION_END) 
    {
        MLV_get_mouse_position(&mouseX, &mouseY);
    }

}

/*
    Fonction permettant de gérer le clique de la souris
*/
void* mouseClick(void* args)
{
    int mouseX;
    int mouseY;
    int selected_value;
    struct SlotLocation slot;
    SudokuGrid forbiddenGrid = grids.forbiddenGrid;
    SudokuGrid gameGrid = grids.gameGrid;

    /* On écoute la souris tant que le programme tourne*/
    while(1 && getCurrentAction() != ACTION_END) 
    {
        MLV_wait_mouse(&mouseX, &mouseY); /* Fonction bloquante qui se débloque au clique*/
        
        /* Gestion de la souris lors du déroulé de la partie*/
        if(!isGridFull(gameGrid)) /*On vérifie si la grille est pleine pour cela*/
        {
            if(getSlotFromCoordinates(mouseX, mouseY, &slot)) /* On récupère la case à partir des coordonées de la souris*/
            {
                
                if(forbiddenGrid[gridOffset(slot.x1,slot.y1,slot.x2,slot.y2)] == 0) /* Si cette case n'a pas de valeur par défaut alors ont peut la selectionner */ {
                    currentSelectedSlot = slot; /*On active la séléction*/
                    setDrawScore(0);
                } else {
                    emptyCurrentSelectedSlot(); /*Retirer la selection*/
                }
                
            } else if(getSlotChoice(mouseX, mouseY, &selected_value))  /*On vérifie que l'utilisateur a cliqué sur la grille de séléction*/
            {
                /*Si l'utilisateur choisi un numéro*/
                /* On  tente de le placer dans la grille */
                if(playOnGrid(gameGrid, forbiddenGrid, currentSelectedSlot.x1, currentSelectedSlot.y1, currentSelectedSlot.x2, currentSelectedSlot.y2, selected_value))
                {
                    /*Sucess play grid*/
                    emptyCurrentSelectedSlot();/* On enlève la selection*/
                }
                else
                {

                }
        
            } else /* Sinon l'utilisateur a cliqué dans le vide*/
            {
                
            }

        } else{
            /* Gestion de la souris lors de la fin de la partie */
        }
        
        /* On regarde le clique sur les boutons du menu*/
        if(listen_button(mouseX, mouseY, getMenuButtons(0))) setDrawScore(1); /*Afficher les scores*/  

        /*Trouve la solution de la  grille */
        if(listen_button(mouseX, mouseY, getMenuButtons(1))) {
            resolveGrid(grids,0,0);           
            endGame(0);
        }

        /*Met fin au programme*/
        if(listen_button(mouseX, mouseY, getMenuButtons(2))) {
            kill(getppid(), SIGINT);
            exit(0);
        }

        /*Permet de relancer la partie*/
        if(listen_button(mouseX, mouseY, getMenuButtons(3))) restartGame(grids);        

    }
    pthread_exit(NULL);
}

/*Fonction qui renvoie 1 si la souris clique sur le bouton en argument, sinon 0*/
int listen_button(int mouseX, int mouseY, struct MenuButton button)
{       
    if(mouseX > button.x && mouseX < button.x+button.width &&
       mouseY  > button.y && mouseY < button.y+button.height)
        return 1;

    return 0;  
}


void freeListener()
{

}

/* ---------- Fonctions permettant de gérer les slots séléctionés ------------*/
/* Fonction permettant de dire que l'utilisateur n'a aucune casz séléctionnée*/
void emptyCurrentSelectedSlot()
{
    currentSelectedSlot.x1 = -1;
    currentSelectedSlot.y1 = -1;
    currentSelectedSlot.x2 = -1;
    currentSelectedSlot.y2 = -1;
}



/* Fonction permettant de vérifer si l'utilisateur a séléctionné une case */
int slotIsEmpty(struct SlotLocation slotLocation)
{
    if(slotLocation.x1 == -1 || slotLocation.y1 == -1 || slotLocation.x2 == -1 || slotLocation.y2 == -1)
        return TRUE;
    return FALSE;
}

struct SlotLocation getCurrentSelectedSlot() {
    return currentSelectedSlot;
}


int getCurrentOverSlotLocation(struct SlotLocation *overSlotLocation)
{
    int mouseX;
    int mouseY;

    MLV_get_mouse_position(&mouseX, &mouseY);
    getSlotFromCoordinates(mouseX, mouseY, overSlotLocation);

    if(overSlotLocation->x1 == -1 || overSlotLocation->y1 == -1 || overSlotLocation->x2 == -1 || overSlotLocation->y2 == -1)
        return 0;

    return 1;
}


int getCurrentOverSelectorSlot()
{
    int selectorCoordinates;
    int mouseX, mouseY;
    MLV_get_mouse_position(&mouseX, &mouseY);

    if(!getSlotChoice(mouseX, mouseY, &selectorCoordinates)) return -1;

    return selectorCoordinates;
}

