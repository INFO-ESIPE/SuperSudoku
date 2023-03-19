#include <stdio.h>
#include <MLV/MLV_all.h>

#include "mouse.h"

int isClickInGrid(int x, int y, int cell_size, int square_dim, int square_count) {
    int grid_min = cell_size;
    int grid_max = cell_size+square_dim*square_count;

    return(!(x < grid_min || x > grid_max || y < grid_min || y > grid_max));
}

int isInEmptySquare(int x, int y, int cell_size, int square_dim, int square_count, Board grid) {
    int case_x = (x-cell_size)/square_dim;
    int case_y = (y-cell_size)/square_dim;

    return(grid[case_y][case_x] == 0);
}

int isInChoiceGrid(int x, int y, int cell_size, int square_dim, int square_count) {
    int case_x = (x-cell_size)/square_dim;
    int case_y = (y-cell_size)/square_dim;

    return(case_x >= 10 && case_x <= 12 && case_y >= 3 && case_y <= 5);
}

int updateGrid(int x, int y, int old_x, int old_y, int cell_size, int square_dim, int square_count, Board grid, Board Choice) {
    int case_x = (x-cell_size)/square_dim;
    int case_y = (y-cell_size)/square_dim;

    int previous_case_x = (old_x-cell_size)/square_dim;
    int previous_case_y = (old_y-cell_size)/square_dim;

    grid[previous_case_y][previous_case_x] = Choice[case_y-3][case_x-10];

    return 0;
}