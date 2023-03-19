#include <stdio.h>
#include <MLV/MLV_all.h>

#include "sudoku.h"
#include "in_out.h"
#include "drawboard.h"
#include "mouse.h"

#define window_width 1200
#define window_height 800

int square_count;
int square_dim;
int cell_size;

int main(int argc, char* argv[]) {
    Board B;
    Board Choice;

    initialise_grid_choice(Choice);

    //On check si on a bien un 2e argument passé en paramètre sinon on insulte l'utilisateur (ce gros nullos)
    if (argc < 2)
    {
        fprintf(stderr, "Il manque une grille là coco\n Tu peux en mettre une en paramètre (data/grid1.txt) ou faire un (make run)\n");
        return 1;
    }

    //Donne les infos de la grille en paramètre dans l'instance board
    fread_board(argv[1], B);

    //Ptit affichage de la grille avec les numéros dans le terminal pour être sûr
    print_board(B);

    square_count = 9;
    square_dim = window_height/(square_count+1);
    cell_size = square_dim/3;
    int game_state = 1;
    int x = 0;
    int y = 0;
    int old_x, old_y;


    MLV_create_window("SUDOKU", NULL, window_width, window_height);
    MLV_clear_window(MLV_COLOR_WHITE);

    while (game_state) {
        drawBoard(square_count, square_dim, cell_size, B);

        MLV_actualise_window();
        old_x = x;
        old_y = y;
        MLV_wait_mouse(&x, &y);

        MLV_clear_window(MLV_COLOR_WHITE);
		
        if(isClickInGrid(x, y, cell_size, square_dim, square_count) && isInEmptySquare(x, y, cell_size, square_dim, square_count, B)) {
            isInChoiceGrid(x, y, cell_size, square_dim, square_count);
            drawChoicesBoard(square_count, square_dim, cell_size, Choice);
            drawChoicesSquare(x, y, cell_size, square_dim);
        } else if(isInChoiceGrid(x, y, cell_size, square_dim, square_count)) {
            updateGrid(x, y,old_x, old_y, cell_size, square_dim, square_count, B, Choice);
        }
        if(!is_full_grid(B)) {
            break;
        }
    }
    MLV_free_window();    
    return 0;
}