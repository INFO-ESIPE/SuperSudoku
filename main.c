#include <stdio.h>
#include <stdlib.h>

/* Bibliothèque pour gérer l'aléatoire*/
#include <time.h>

/* Constantes nécéssaire au programme */
#include "headers/constants.h"

/* Headers permettant de gérer la grille*/
#include "headers/grid_generator.h"
#include "headers/grid_utility.h"




/* On prépare la partie en mémoire*/
void prepareDataGrid()
{

    /* Fonction pour générer une grille aléatoire et l'afficher à la console*/
    struct SuperSudoku grids = generateMainGrid();
    printf("\n       Grille de départ\n");
    consolePrintMainGrid(grids.gameGrid);
    
}



/* Fonction main du programme*/
int main(int argc, char* argv[])
{
	srand(time(NULL)); /* Permet de gérer l'aléatoire pour les besoins futurs du programme*/


    prepareDataGrid(); /* Permet de préparer la grille proprement*/
    

    /* Fin du programme */
    return EXIT_SUCCESS;
}
