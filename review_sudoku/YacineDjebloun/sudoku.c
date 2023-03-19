#include <stdio.h>

#include "sudoku.h"

void print_board(Board grid){
    int i,j;
    for (i = 0 ; i < 9 ; i++) {
        
        printf("-------------------------------------");

        printf("\n");

        for(j = 0 ; j < 9 ; j++) {
            printf("|");
            printf(" ");
            if (grid[i][j] != 0) {
                printf("%d", grid[i][j]);
            } else {
                printf(" ");
            }
            printf(" ");
        }
        printf("|\n");
    }
    printf("-------------------------------------\n");
}

int is_full_grid(Board grid) {
    int i,j;
    for (i = 0 ; i < 9 ; i++) {
        for (j = 0 ; j < 9 ; j++) {
            if(grid[i][j] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int check_line_column(Board grid, int i, int j, int n) {
    int incr = 0;
    for(incr = 0; incr < 9; incr++){
        if(grid[incr][j] == n){
            return 0;
        }
        if(grid[i][incr] == n){
            return 0;
        }
    }
    return 1;
}

int check_square(Board grid, int i, int j, int n) {
    int incr = 0;
    int i_h = 3*(i/3);
    int j_g = 3*(j/3);
    for(incr = 0; incr < 3; incr++){
        if(grid[i_h + incr][j_g] == n){
            return 0;
        }
        if(grid[i_h + incr][j_g + 1] == n){
            return 0;
        }
        if(grid[i_h + incr][j_g + 2] == n){
            return 0;
        }
    }
    return 1;
}
 
int contraintes(Board grid, int i, int j, int n) {
    if(check_line_column(grid, i, j, n) == 0) {
        return 0;
    }

    if(check_square(grid, i, j, n) == 0) {
        return 0;
    }
    
    return 1;
}

void solver(Board grid) {
    int i,j,n;
    if (is_full_grid(grid) == 0) {
        print_board(grid);
    } else {
        for(i = 0 ; i < 9 ; i++) {
            for(j = 0 ; j < 9 ; j++) {
                if (grid[i][j] == 0) {
                    /*permutations*/
                    for(n = 1; n < 10; n++) {
                        if(contraintes(grid, i, j, n) == 1) {
                            grid[i][j] = n;
                            solver(grid);
                            grid[i][j] = 0;
                        }
                    }
                    return;
                }
            }
        }
    }
}

int initialise_grid_choice(Board choice) {
    int number = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            choice[i][j] = number;
            number++;
        }
    }
    return 0;
}