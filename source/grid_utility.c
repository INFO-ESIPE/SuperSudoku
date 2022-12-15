#include <stdio.h>
#include <stdlib.h>

#include "../headers/grid_utility.h"
#include "../headers/constants.h"

/* 
    La grille de sudoku étant en 1 dimension dans la mémoire, il est possible grace à cette fonction de récupérer une case dans une cellule en 4D
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
int playOnGrid(SudokuGrid gameGrid, SudokuGrid forbiddenGrid, int x1, int y1, int x2, int y2, int value)
{
    /*
    printf("Try to play %d in slot (%d,%d,%d,%d)\n", value, x1, y1, x2, y2);
    printf("gameGrid(%d), forbiddenGrid(%d)\n", gameGrid[gridOffset(x1,y1,x2,y2)], forbiddenGrid[gridOffset(x1,y1,x2,y2)]);
    */
    /* Si il n'est pas possible de jouer à cette case d'après les règles du sudoku*/
    if(!isSlotCompatibleInGrid(gameGrid, x1, y1, x2, y2, value))
        return FALSE;
    
    /* Si l'on tente de jouer sur une case avec un chiffre généré par défaut, on annule*/
    if(forbiddenGrid[gridOffset(x1,y2,x2,y2)] == 1)
        return FALSE;
    

    /* Sinon, on change la valeur de la case */
    gameGrid[gridOffset(x1,y1,x2,y2)] = value;

    consolePrintMainGrid(gameGrid);
    
    return TRUE;
}

/*Fonction qui renvoie 1 si toutes les cases de la grille sont valides et 0 sinon*/
int isGridCorrect(SudokuGrid gameGrid)
{
    int i, j, k, l;

    for(i = 0; i < NB_SUBGRID/3; i++)
        for(j = 0; j < NB_SUBGRID/3; j++)
            for(k = 0; k < NB_SLOT_SUBGRID/3; k++)
                for(l = 0; l < NB_SLOT_SUBGRID/3; l++)
                    if(isSlotCompatibleInGrid(gameGrid, i, j, k, l, gameGrid[gridOffset(i,j,k,l)]))
                        return 0;
    return 1;
}

/*Fonction qui renvoie 1 si aucune case de la grille n'est vide, sinon 0*/
int isGridFull(SudokuGrid gameGrid)
{
    int i;
    for(i = 0; i < NB_SLOT_SUBGRID*NB_SLOT_SUBGRID; i++) {
        if(gameGrid[i] == 0) return 0;
    }
    return 1;
}

/* 
    Cette fonction prend en argument une grille générée avec GenerateMainGrid pour l'afficher à la console
*/
void consolePrintMainGrid(SudokuGrid grid)
{
    int k;
    int l;
    
    printf("|---------|---------|---------|\n");
    for(l = 0; l < 9; l+=1)
    {
        printf("|");
        for(k = 0; k < 9; k+=1)
        {
            printf(" %d ", grid[k+(l*9)]);
            if((k+1)%3 == 0) printf("|");
        }
        if((l+1)%3 == 0) printf("\n|---------|---------|---------|");
        printf("\n");
    }
}
