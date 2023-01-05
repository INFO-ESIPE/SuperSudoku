/*
	Programmation C - TP7
	Max Ducoudré - INFO1
    Fonctions permettant de gérer le solveur de la grille de sudoku
*/

#include <stdio.h>
#include <stdlib.h>

#include "../headers/sudoku_solver.h"


/*Fonction permettant de résoudre la grille de sudoku*/
int resolveGrid(struct SuperSudoku grids, int x, int y)
{
    /*printf("%d = %d\n", grids.gameGrid[gridOffset(0,0,0,0)], grids.gameGrid[gridOffset2D(0,0)]);*/
    /*playOnGrid(grids.gameGrid, grids.forbiddenGrid,0,0,0,0,5);*/
    int k;
    if (x == 9 - 1 && y == 9) return 1;
    if(y == 9) {
        x++;
        y = 0;
    }

    if (grids.gameGrid[gridOffset2D(x,y)] > 0) return resolveGrid(grids, x, y + 1);

    for(k = 1; k <= 9; k++) {
        if(can_play_value(grids, x, y, k))
        {
            grids.gameGrid[gridOffset2D(x,y)] = k;
            if(resolveGrid(grids, x, y+1)) return 1; 
        }
        grids.gameGrid[gridOffset2D(x,y)] = 0;
    }
    return 0;    
}

/*Fonction qui renvoie 1 si on peux jouer la valeur value à l'emplacement x y ou 0 si ce n'est pas possible*/
int can_play_value(struct SuperSudoku grids, int x, int y, int value)
{
    int i,j;
    
    /*Vérification des arguments*/
    if(grids.forbiddenGrid[gridOffset2D(x,y)] != 0){
        return 0;
    }
    if(value > 9 || value < 1) {
        return 0;
    }


    /* Vérification des cases voisines*/
    for(i = 0; i<3; i++) {
        for(j = 0; j<3; j++) {
            if(grids.gameGrid[gridOffset2D((x+((x/3)*3)),(y+((y/3)*3)))] == value) {
                return 0;
            }
        }
    }

    /* Vérification ligne colonnes*/
    for(i = 0; i < 9; i++) {
        if(grids.gameGrid[gridOffset2D(x,i)] == value && (i != y)) {
            return 0;
        }
    }

    /*Vérification des lignes*/
    for(i = 0; i < 9; i++){
        if(grids.gameGrid[gridOffset2D(i,y)] == value && (i != x)) {
            return 0;
        } 
    }

    return 1;
}


/*Permet d'accéder à une grille de sudoku comme si c'était un tableau en deux dimensions*/
int gridOffset2D(int x, int y)
{
    return ((9*x) + y);
}