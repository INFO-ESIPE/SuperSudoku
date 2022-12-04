#include <stdio.h>
#include <stdlib.h>

/* Bibliothèque pour gérer l'aléatoire*/
#include <time.h>

/* Constantes nécéssaire au programme */
#include "headers/constants.h"

/* Headers permettant de gérer la grille*/
#include "headers/grid_generator.h"
#include "headers/grid_utility.h"

/* Headers permettant de gérer l'affichage graphique*/
#include "headers/grid_frame.h"



/* On prépare la partie en mémoire*/
void prepareGrid()
{

    /* Fonction pour générer une grille aléatoire et l'afficher à la console*/
    
    struct SuperSudoku grids = generateMainGrid();
    printf("\n       Grille de départ\n");
    consolePrintMainGrid(grids.gameGrid);

    printf("\n       Grille d'interdits\n");
    consolePrintMainGrid(grids.forbiddenGrid);
    


    /* Gestion de l'affichage graphique */
    generateGridFrame(grids);

        


    /*
        int success = playOnGrid(grids, 0, 0, 0, 0, 2);
        printf("Succes : %d\n", success);
        consolePrintMainGrid(grids.gameGrid);
    */

    
}




/* Fonction main du programme*/
int main(int argc, char* argv[])
{
	srand(time(NULL)); /* Permet de gérer l'aléatoire pour les besoins futurs du programme*/


    prepareGrid(); /* Permet de préparer la grille proprement (données & affichage graphique)*/
    

    /* Fin du programme */
    return EXIT_SUCCESS;
}
