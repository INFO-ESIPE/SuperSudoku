#include <stdio.h>
#include <stdlib.h>

#include "../headers/grid_utility.h"
#include "../headers/constants.h"

/* 
    La grille de sudoku étant en 1 dimension dans la mémoire, il est possible grade à cette fonction de récupérer une case dans une cellule
    x1 et y1 corrrespondent aux coordonées d'une cellule de la grille
    x2 et y2 correspondent aux coordonées d'une case de la cellule x1,y1
*/
int gridOffset(int x1, int y1, int x2, int y2) 
{ 
    return (x1*27 + y1*3 + x2*9 + y2);
}

/*
    Cette fonction vérifie si à la case x1,y1,x2,y2 il est possible d'y placer la valeur "value".
    Si c'est le cas, elle renvoi 1, sinon 0
*/
int isSlotCompatibleInGrid(SudokuGrid grid, int x1, int y1, int x2, int y2, int value)
{
    int i,j;

    /*On regarde si le numéro n'est pas déjà dans la sous-grille de 9 */
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(!(x2 == i && y2 == j))
            {
                if(value == grid[gridOffset(x1,y1,i,j)])
                {
                    return FALSE;
                }
            }
        }
    }

    /* Si ce n'est pas le cas, on regarde s'il n'est présent ni dans la même ligne, ni dans la même colonne */
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            /* Colonnes */
            if(value == grid[gridOffset(x1,i, x2, j)])
                return FALSE;
            /* Lignes */
            if(value == grid[gridOffset(i, y1, j, y2)])
                return FALSE;
        }
    }

    /* Sinon, c'est que la valeur peut être placée*/
    return TRUE;
}

/*
    Cette fonction permet de jouer un coup avec la valeur "value" sur la grille sur la cellule x1,y1 à la case x2,y2 
    Elle renvoi 1 si le coup a pu être joué et 0 sinon
*/
int playOnGrid(struct SuperSudoku grids, int x1, int y1, int x2, int y2, int value)
{
    /* Si il n'est pas possible de jouer à cette case d'après les règles du sudoku*/
    if(!isSlotCompatibleInGrid(grids.gameGrid, x1, y1, x2, y2, value))
        return FALSE;

    /* Si l'on tente de jouer sur une case avec un chiffre généré par défaut, on annule*/
    if(grids.forbiddenGrid[gridOffset(x1,x2,y1,y2)] == 1)
        return FALSE;
    

    /* Sinon, on change la valeur de la case */
    grids.gameGrid[gridOffset(x1,y2,x2,y2)] = value;
    return TRUE;
}