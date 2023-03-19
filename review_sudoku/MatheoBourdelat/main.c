#include <MLV/MLV_all.h>
#include <stdio.h>
#include "sudoku.h"
#include "in_out.h"
#include "graph.h"



int main (int argc, char* argv[]){

    Board board;

    /* Si la grille n'est pas mise en argument de l'appelle du programme */

    if (fread_board(argv[1], board)==0)
    {
        printf("Grille introuvable\n");
        exit(1);
    }

    /* Appelle de la fonction pour afficher la grille de sudoku dans le terminal */

    print_board(board);

    generate_frame(board);

    return 0;

}