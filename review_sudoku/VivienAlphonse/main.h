#ifndef MAIN_H
#define MAIN_H

#define TITLE "SUDOKU"
#define WIDTH 1800
#define HEIGHT 900
#define SIZE_OF_GRID 9

#define SHOW_RIGHT_ANSWERS_IN_VALUE_SELECTOR_GRID 0 /* 0 for yes and 1 for no */

struct Grid_properties
{
    char *title;
    int width;
    int size;
    int cell_size;
    int margin;
};

typedef int Board[SIZE_OF_GRID][SIZE_OF_GRID];

#endif /* MAIN_H */
