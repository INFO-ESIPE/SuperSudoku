#include <MLV/MLV_all.h>
#include <stdio.h>
#include "graph.h"

int last_x, last_y;

/* Génération de la grille de sudoku à partir de la grille  */

int generate_frame(Board board){

    last_x = -1;
    last_y = -1;


    MLV_create_window( "BOURDELAT Mathéo - Sudoku", "Sudoku", WIN_HEIGHT, WIN_WIDTH );

    /* Tant que les fonctions return 1, on continue a afficher la fenêtre de sudoku */
    while(1){

        MLV_clear_window(MLV_COLOR_BLACK);

        /* Appelle de la fonction pour afficher les grilles de sudoku */
        draw_grille(board); 
        /* Si on clique en dehors de la grille de sudoku  */
        if (last_x != -1 && last_y != -1)
        {
            draw_tab(board); 
        }
        MLV_actualise_window();
        listen_mouse(board);
    }

    MLV_free_window();
}

/* Fonction qui affiche les numéros dans les carrés du sélecteur */

int draw_tab(Board board){
    int i;
    int j;
    int k = 0;
    char buffer[10];

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            MLV_draw_rectangle(MARGE*2 + (9+i)*TAILLE_CASE, (4+j) * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, MLV_COLOR_WHITE);
            k++;
            sprintf(buffer, "%d", k);
            MLV_draw_text(MARGE*2 + (9+j)*TAILLE_CASE + 40, (4+i) * TAILLE_CASE + 40, buffer, MLV_COLOR_WHITE);
        }       
    }
}

/* Fonction qui affiche les numéros dans les carrés de la grille du sudoku */

int draw_grille(Board board){
    int i;
    int j;
    char buffer[10];

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            MLV_draw_rectangle(MARGE + i*TAILLE_CASE, MARGE + j*TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, MLV_COLOR_WHITE);
            
            if (board[i][j]!=0){
                sprintf(buffer, "%d", board[i][j]);
                MLV_draw_text(MARGE + j*TAILLE_CASE + 40, MARGE + i*TAILLE_CASE + 40, buffer, MLV_COLOR_WHITE);

            }
        }      
    }
}

/* Fonction qui récupère les coordonnées de la souris en pixel */

int listen_mouse(Board board){
    int mouse_x;
    int mouse_y;
    int i, j;

    MLV_wait_mouse(&mouse_x, &mouse_y);
    printf("click on %d %d\n", mouse_x, mouse_y);

    /* Appelle de la foncion pix_to_game permmettant d'afficher les coordonées de la souris en coordonnées sur le tableau */
    if(pix_to_game(mouse_x, mouse_y, &i, &j)){
        printf("click on index %d %d = %d\n", i, j, board[i][j]);
        last_x = i;
        last_y = j;

        return 1;
    }

    /* Appelle de la foncion pix_to_game permmettant d'afficher les coordonées de la souris en coordonnées sur le sélecteur */
    if(pix_to_select(mouse_x, mouse_y, &i)){
        if (last_x != -1 && last_y != -1)
        {   
            /* Si la fonction validation return 1, alors on affiche le sélecteur et on remplace la case vide par un numéro jouable */
            if (validation(board, last_x, last_y, i)==1)
            {
                board[last_x][last_y] = i;
                last_x = -1;
                last_y = -1;
            }    
        }
        printf("Click on selector : %d\n", i);
        return 2;
    }
    last_x = -1;
    last_y = -1;
    return 0;
}

/* Fonction convertisant les coordonées en pixel de la grille de sudoku en coordonées de numéro sur la grille de sudoku */

int pix_to_game(int x, int y, int* i, int* j){

    int k, l;

    for (k = 0; k < 9; k++)
    {
        for (l = 0; l < 9; l++)
        {
            if (x > MARGE + (l*TAILLE_CASE) && x < MARGE +((l+1)*TAILLE_CASE))
            {
                if (y > MARGE + (k*TAILLE_CASE) && y < MARGE +((k+1)*TAILLE_CASE)){
                    *i = k;
                    *j = l;

                    return 1;
                }
                
            }
            
        }
        
    }

    return 0;
    
}

/* Fonction convertisant les coordonées en pixel du sélecteur en coordonées de numéro sur le sélecteur */

int pix_to_select(int x, int y, int* k){
    int i, j;
    int m = 0;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            m++;
            if (x > MARGE*2 + (9+j)*TAILLE_CASE && x < MARGE*2 + (9+j+1)*TAILLE_CASE)
            {
                if (y > (4+i) * TAILLE_CASE && y < (4+i+1) * TAILLE_CASE){
                
                    
                    *k = m;
                    return 1;
                }
                
            }
            
        }
        
    }

    return 0;

}