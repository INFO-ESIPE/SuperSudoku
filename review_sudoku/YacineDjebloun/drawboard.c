#include <MLV/MLV_all.h>

#include "drawboard.h"

int drawSquareCenter(int sqr, int cell_size, int square_dim) {
    return cell_size+sqr-(square_dim/2);
}

int getCenterCoord(int sqr, int cell_size, int square_dim) {
    return ((sqr-cell_size)/square_dim)*square_dim+cell_size+square_dim/2;
}

int drawBoard(int square_count, int square_dim, int cell_size, Board grid) {
    char string[2];
    char s;
    for (int i = 0 ; i < square_count ; i++) {
        for(int j = 0 ; j < square_count; j++) {
            MLV_draw_rectangle(j*square_dim+cell_size,i*square_dim+cell_size,square_dim, square_dim, MLV_COLOR_BLACK);
        }
    }

    for (int i = 0 ; i < square_count ; i++) {
        for (int j = 0 ; j < square_count ; j++) {
            if(grid[i][j] != 0) {
                s = grid[i][j] + '0';
                string[0] = s;
                string[1] = '\0';
                MLV_draw_text(drawSquareCenter(j*square_dim, cell_size, square_dim)+square_dim, drawSquareCenter(i*square_dim, cell_size, square_dim)+square_dim, string, MLV_COLOR_BLACK);
            }
        }
    }

    return 0;
}

int drawChoicesBoard(int square_count, int square_dim, int cell_size, Board choice) {
    char string[2];
    char s;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            s = choice[i][j] + '0';
            string[0] = s;
            string[1] = '\0';
            MLV_draw_rectangle((j+10)*square_dim+cell_size,(i+3)*square_dim+cell_size,square_dim,square_dim,MLV_COLOR_BLACK);
            MLV_draw_text(drawSquareCenter((j+10)*square_dim, cell_size, square_dim)+square_dim, drawSquareCenter((i+3)*square_dim, cell_size, square_dim)+square_dim, string, MLV_COLOR_BLACK);
        }
    }
    return 0;
}

int drawChoicesSquare(int x, int y, int cell_size, int square_dim) {
    MLV_draw_filled_rectangle(getCenterCoord(x, cell_size, square_dim),getCenterCoord(y, cell_size, square_dim), 20, 20, MLV_COLOR_WHITE);
    MLV_draw_text(getCenterCoord(x, cell_size, square_dim),getCenterCoord(y, cell_size, square_dim),"?",MLV_COLOR_BLUE);
    return 0;
}