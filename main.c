#include <stdio.h>
#include <stdlib.h>

/* Bibliothèque pour gérer l'aléatoire*/
#include <time.h>

/* Constantes nécéssaire au programme */
#include "headers/constants.h"

/* Headers permettant de gérer la grille*/
#include "headers/grid_generator.h"
#include "headers/grid_utility.h"

/* Header permettant de gérer l'affichage graphique*/
#include "headers/grid_frame.h"




/* Permet de récupérer les signaux*/
#include <signal.h>
#include <unistd.h>

#define NO_FILE "NO_FILE_PATH"

struct SuperSudoku mainSuperSudoku;

void freeMemory();
void prepareGame(char* filePath);
void printUsage(char* exName);
void checkArguments(int argc, char * argv[]);

/* Fonction main du programme*/
int main(int argc, char* argv[])
{
	srand(time(NULL)); /* Permet de gérer l'aléatoire pour les besoins futurs du programme*/
    signal(SIGINT, freeMemory); /*Permet de finir le programme proprement quand un signal SIGINT est envoyé par l'utilisateur*/
    checkArguments(argc, argv); /*Fonction permettant de vérifier les options/arguments du programme*/
        
        
    /* Fin du programme */
    return EXIT_SUCCESS;
}

/*Fonction expliquant à l'utilisateur comment utiliser le programme*/
void printUsage(char* exName)
{
    printf("Usage & options:\n");
    printf("%s                       Start sudoku with random grid.\n",exName);
    printf("%s -g <gridFilePath>     Start sudoku with grid specified in file gridFilePath.\n", exName);
    exit(EXIT_FAILURE);
}

/* Vérification des arguments du programme*/
void checkArguments(int argc, char * argv[])
{
    if(argc == 1) {
        prepareGame(NO_FILE); /* Permet de préparer la grille proprement (données & affichage graphique)*/
    }
    else if(argc == 3) {
        if(argv[1][0] == '-') {
            if(argv[1][1] == 'g') {
                prepareGame(argv[2]); /* Permet de préparer la grille proprement à partir d'un fichier (données & affichage graphique)*/
            } else printUsage(argv[0]);
        } else printUsage(argv[0]);   
    }else printUsage(argv[0]);
}

/* On prépare la partie en mémoire*/
void prepareGame(char* filePath)
{
    /* On vérifie si un fichier de grille a été utilisé en argument*/
    if(!strcmp(filePath, NO_FILE)) mainSuperSudoku = generateMainGrid(); /* Fonction pour générer une grille aléatoire */
    else  mainSuperSudoku = generateMainGridFromFile(filePath); /* Fonction pour générer une grille à partir d'un fichier*/
    
    startGame(); /* Lancement de la partie*/
    
    printf("\n       Grille de départ\n");
    consolePrintMainGrid(mainSuperSudoku.gameGrid);

    printf("\n       Grille d'interdits\n");
    consolePrintMainGrid(mainSuperSudoku.forbiddenGrid);
    

    /* Gestion de l'affichage graphique */
    generateGridFrame(mainSuperSudoku); /*fonction bloquante*/
}

/*Libère la mémoire utilisée durant le programme*/
void freeMemory()
{
    printf("End of sudoku\n");
    freeGrids(mainSuperSudoku);
    printf("freeGrids()\n");
    freeFrame();
    printf("freeFrame()\n");

}
