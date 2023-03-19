#include <stdio.h>

#include <stdlib.h>

#include "sudoku.h"

#define SIZE 9


/*Affiche la grille de sudoku*/
void print_board(Board grid) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf(" %d ", grid[i][j]);
            if ((j == 2) || (j == 5)) {
                putchar('|');
            }

        }
        printf("\n");
        if ((i == 2) || (i == 5)) {
            printf("\n----------------------------\n");
        }
    }

}

/*Trouve s'il y a un trou, donc une case qui est égal à 0 dans la grille de sudoku*/
int trouve_trou(Board grid, int* ligne, int* colonne) {
    int i;
    int j;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < 9; j++) {
            if (grid[i][j] == 0 ) {
                *ligne = i;
                *colonne = j;

                return 1;

            }

        }
    }
    return 0;
}

int validation(Board grid, int ligne, int colonne, int j) {
    int corner_x = ligne / 3 * 3;
    int corner_y = colonne / 3 * 3;
    int x;

    for (x = 0; x < SIZE ; x++) {
        if (grid[ligne][x] == j) return 0;
        if (grid[x][colonne] == j) return 0;
        if (grid[corner_x + (x % 3)][corner_y + (x / 3)] == j) return 0;
    }
    return 1;
}

/*Résout la grille de sudoku*/
int solver(Board grid) {
    int ligne;
    int colonne;
    int i;

    if (trouve_trou(grid, &ligne, &colonne) == 0) return 1;

    for (i = 1; i < 10; i++) {
        if (validation(grid, ligne, colonne, i)) {
            grid[ligne][colonne] = i;

            if (solver(grid)) return 1;
            grid[ligne][colonne] = 0;
        }
    }
    return 0;
}
