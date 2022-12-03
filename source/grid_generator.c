#include <stdio.h>
#include <stdlib.h>

#include "../headers/grid_generator.h"
#include "../headers/grid_utility.h"
#include "../headers/constants.h"


/*
    Cette fonction renvoi un tableau contenant une grille de sudoku à résoudre
    Ce tableau est divisé en 4 dimensions (3x3 cellules de 3x3 cases chacunes)
*/
struct SuperSudoku generateMainGrid()
{
    int i,j;
    struct SuperSudoku superSudoku;

    superSudoku.gameGrid = malloc(NB_SLOT_SUBGRID*NB_SUBGRID*sizeof(float*));
    superSudoku.forbiddenGrid = malloc(NB_SLOT_SUBGRID*NB_SUBGRID*sizeof(float*));

    for(i = 0; i < 3; i++) 
        for(j = 0; j < 3; j++) 
            generateSubGrid(superSudoku, i, j);
            
    return superSudoku;
}

/* 
    Cette fonction rempli de manière aléatoire une cellule 3x3 tout en respectant les règles du sudoku
    Elle se base sur la constante EMPTY_SLOT_RATIO pour les cellules vides
    Elle renvoi une grille contenant des 1 aux endroits où il y au ne valeur non modifiable et 0 aux endroits où l'on peut jouer
*/
void generateSubGrid(struct SuperSudoku grids, int subGridX, int subGridY)
{
    int i,j;
    int tmp_rand;
    int tmp_ban_list[NB_SLOT_SUBGRID];
    
    for(i = 0; i < NB_SLOT_SUBGRID; i++) tmp_ban_list[i] = 0;

    for(i = 0; i < 3; i++) 
    {
        for(j = 0; j < 3; j++)
        {
            if(rand()%100 < EMPTY_SLOT_RATIO) 
            {   
                grids.gameGrid[gridOffset(subGridX, subGridY, i, j)] = EMPTY_SLOT; 
            }
            else
            {
                tmp_rand = rand()%((9)-1) + 1;
                if(tmp_ban_list[tmp_rand-1] == 0)
                {
                    if(isSlotCompatibleInGrid(grids.gameGrid,subGridX,subGridY, i, j, tmp_rand)) 
                    {
                        grids.gameGrid[gridOffset(subGridX, subGridY, i, j)] = tmp_rand;
                        grids.forbiddenGrid[gridOffset(subGridX, subGridY, i, j)] = 1;
                        tmp_ban_list[tmp_rand-1] = 1;
                    }
                }
            }
        }
    }
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

/*
    Cette fonction libère la mémoire demandée par la grille
*/
void freeGrids(struct SuperSudoku grids)
{
    free(grids.gameGrid);
    free(grids.forbiddenGrid);
}