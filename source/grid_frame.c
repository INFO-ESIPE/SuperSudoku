#include <stdio.h>
#include <stdlib.h>

#include "../headers/grid_frame.h"


/* Variable permettant de dire si oui ou non on dessine la grille de séléction de numéro */
int drawNumSelect = FALSE;
struct SlotLocation currentSelectedSlot = {-1,-1,-1,-1};

/* Fonction permettant de générer la fenêtre contenant la grille de sudoku*/
void generateGridFrame(struct SuperSudoku grids)
{
    int action = ACTION_EMPTY;

    MLV_create_window(GAME_NAME, "../resources/Sudoku.png", WIN_WIDTH, WIN_HEIGHT); /* Création de la fenêtre*/
    startListenMouse(grids);  /*Ecoute le clique de la souris*/
    startDrawUpdate(grids); /* On actualise la grid en temps réel en fonction de la modification des données dans stockés dans SuperSoduku*/

    /* On boucle jusqu'à la fin du jeux
    Cette boucle nous permet de récupérer l'action du joueur*/
    while (action != ACTION_END)
    {
        if(action == ACTION_EMPTY)
        {
            MLV_wait_milliseconds(WAIT_TIME_MILLISEC);
        }
    }
}

/*
    Prend en argument des coordonées x y sur la fenêtre et modifie selected_value avec la valeur choisie par l'utilisateur
    Renvoi 1 si la fonction a réussie et 0 sinon
 */
int getSlotChoice(int mouseX, int mouseY, int* selected_value)
{
    int i,j, k;
        /*MLV_draw_rectangle(MARGIN_LEFT*2 + SLOT_SIZE*9, MARGIN_TOP + SLOT_SIZE*3, SLOT_SIZE*3, SLOT_SIZE*3, ORANGE);*/

    if(currentSelectedSlotIsEmpty()) return FALSE;
    k = 1;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
        {
            if(
                mouseX > MARGIN_LEFT*2 + SLOT_SIZE*9 + (j*SLOT_SIZE) && mouseX < MARGIN_LEFT*2 + SLOT_SIZE*9 + ((j+1)*SLOT_SIZE) &&
                mouseY > MARGIN_TOP + SLOT_SIZE*3 + (i*SLOT_SIZE) && mouseY < MARGIN_TOP + SLOT_SIZE*3 + ((i+1)*SLOT_SIZE)
            )
            {
                *selected_value = k;
                return TRUE;
            }
            k++;

        }

    return FALSE;
}

/* 
    Prend en argument des coordonées x y sur la fenêtre et modifie SlotLocation avec le numéro de la cellule et de la case
    Renvoi 1 si la fonction a réussi et 0 sinon
*/
int getSlotFromCoordinates(int x, int y, struct SlotLocation *slot)
{
    /*struct SlotLocation slot;*/
    int cellX,cellY,slotX,slotY;
    slot->x1 = -1;
    slot->y1 = -1;
    slot->x2 = -1;
    slot->y2 = -1;

    /* On vérifie si le clique est en dehors de la grille*/
    if(x < MARGIN_LEFT || y < MARGIN_TOP || x > MARGIN_LEFT+GRID_WIDTH || y > MARGIN_LEFT+GRID_HEIGHT) return 0;

    /* Sinon on test les coordonées pour chaque cases*/
    /* TODO : Optimiser en mettant des conditions entre les boucles */
    for(cellX = 0; cellX < 3; cellX++)
        for(cellY = 0; cellY < 3; cellY++)
            for(slotX = 0; slotX < 3; slotX++)
                for(slotY = 0; slotY < 3; slotY++)
                    if(
                        x > MARGIN_LEFT + (cellX * (SLOT_SIZE * 3)) && x < MARGIN_LEFT + ((cellX+1) * (SLOT_SIZE*3)) &&
                        y > MARGIN_TOP  + (cellY * (SLOT_SIZE * 3)) && y < MARGIN_TOP + ((cellY+1) * (SLOT_SIZE*3)) &&
                        x > MARGIN_LEFT + (cellX * (SLOT_SIZE * 3)) + (slotX * (SLOT_SIZE * 1)) && x < MARGIN_LEFT + (cellX * (SLOT_SIZE * 3)) + ((slotX+1) * (SLOT_SIZE * 1)) &&
                        y > MARGIN_TOP + (cellY * (SLOT_SIZE * 3)) + (slotY * (SLOT_SIZE * 1)) && y < MARGIN_TOP + (cellY * (SLOT_SIZE * 3)) + ((slotY+1) * (SLOT_SIZE * 1))
                        )
                        {
                            slot->x1 = cellY;
                            slot->y1 = cellX;
                            slot->x2 = slotY;
                            slot->y2 = slotX;
                            return 1;
                        }
    return 0;
}

/* Fonction permettant d'activer l'écoute de la souris avec un thread*/
void startListenMouse(struct SuperSudoku grids)
{
    pthread_t threadMouseID;
    pthread_create(&threadMouseID, NULL, &mouseClick, &grids);

}

/*
    Fonction permettant de gérer le clique de la souris
*/
/*TODO : Placer cette fonction dans mouse_listener.c*/
void* mouseClick(void* args)
{
    int mouseX;
    int mouseY;
    int selected_value;
    struct SlotLocation slot;
    struct SuperSudoku *grids = args;
    SudokuGrid forbiddenGrid = grids->forbiddenGrid;

    while(1)
    {
        MLV_wait_mouse(&mouseX, &mouseY); /* Fonction bloquante qui se débloque au clique*/

        if(getSlotFromCoordinates(mouseX, mouseY, &slot)) /* On récupère la case à partir des coordonées de la souris*/
        {
            if(forbiddenGrid[gridOffset(slot.x1,slot.y1,slot.x2,slot.y2)] == 0) /* Si cette case n'a pas de valeur par défaut alors ont peut la selectionner */
            {
                currentSelectedSlot = slot; /*On active la séléction*/
            }
            else
            {
                emptyCurrentSelectedSlot(); /*Retirer la selection*/
            }
            
        } else if(getSlotChoice(mouseX, mouseY, &selected_value))  /*On vérifie que l'utilisateur a cliqué sur la grille de séléction*/
        {
            printf("Value selected : %d\n", selected_value);
            /*Si l'utilisateur choisi un numéro*/

            /* On  tente de le placer dans la grille*/
            playOnGrid(grids, currentSelectedSlot.x1, currentSelectedSlot.y1, currentSelectedSlot.x2, currentSelectedSlot.y2, selected_value);

            /* On enlève la selection*/
            emptyCurrentSelectedSlot();

        } else /* Sinon l'utilisateur a cliqué dans le vide*/
        {

        }

    }
    pthread_exit(NULL);

}

/*Fonction commençant le thread d'actualisation de l'affichage*/
void startDrawUpdate(struct SuperSudoku grids)
{
    pthread_t threadDrawID;
    pthread_create(&threadDrawID, NULL, &updateDraw, &grids);
}



/*Cette fonction met à jour l'affichage en fonction des données envoyé dedans*/
void* updateDraw(void* args)
{
    /* Données de la grille*/
    struct SuperSudoku *grids = args;
    SudokuGrid gameGrid = grids->gameGrid;
    SudokuGrid forbiddenGrid = grids->forbiddenGrid;

    /* Valeurs temporaire pour remplir le tableau*/
    int i, j, k, l;
    int tmp_slot_X, tmp_slot_Y, tmp_slot_Width, tmp_slot_Height;
    char tmp_slot_char[255];
    MLV_Color num_color = BLACK;

    /* Valeurs pour la surbrillance de la case séléctionnée*/
    int tmp_slot_sur_X, tmp_slot_sur_Y, tmp_slot_sur_Width, tmp_slot_sur_Height;


    /* Chargement d'une nouvelle police d'écriture*/
    /* TODO : Le fichier .ttf ne charge pas */
    MLV_Font* font /*= MLV_load_font("../resources/Sudoku.ttf" , 20)*/;


    /* Actualisation de l'affichage en temps réel avec les données des grilles */
    while(1)
    {
        /*--------Section dessin de la grille principale--------*/
        /* Clear l'affichage */
        MLV_draw_filled_rectangle(0, 0, WIN_WIDTH, WIN_HEIGHT, WHITE);

        /* On itère toutes les cases du tableau*/
        for(i = 0; i < 3; i++)
            for(j = 0; j < 3; j++)
                for(k = 0; k < 3; k++)
                    for(l = 0; l < 3; l++)
                    {
                        /* Calcul de la position de la case*/
                        tmp_slot_X = MARGIN_LEFT + (j*SLOT_SIZE*3) + (l*SLOT_SIZE);
                        tmp_slot_Y = MARGIN_TOP + (i*SLOT_SIZE*3) + (k*SLOT_SIZE);
                        tmp_slot_Width = SLOT_SIZE+1;
                        tmp_slot_Height = SLOT_SIZE+1;
                        num_color = BLACK;

                        /*Dessin du contour d'une case*/
                        if(currentSelectedSlot.x1 == i && currentSelectedSlot.y1 == j && currentSelectedSlot.x2 == k && currentSelectedSlot.y2 == l)
                        {
                            tmp_slot_sur_X = MARGIN_LEFT + (j*SLOT_SIZE*3) + (l*SLOT_SIZE);
                            tmp_slot_sur_Y = MARGIN_TOP + (i*SLOT_SIZE*3) + (k*SLOT_SIZE);
                            tmp_slot_sur_Width = SLOT_SIZE+1;
                            tmp_slot_sur_Height = SLOT_SIZE+1;
                        }

                        MLV_draw_rectangle(tmp_slot_X, tmp_slot_Y, tmp_slot_Width, tmp_slot_Height, BLACK);

                        /*Ajout de la valeure dans la case*/
                        if(gameGrid[gridOffset(i,j,k,l)] != 0)
                        {
                            if(forbiddenGrid[gridOffset(i,j,k,l)] == 1) num_color = GRAY;
                            else num_color = BLACK;

                            sprintf(tmp_slot_char, "%d", gameGrid[gridOffset(i,j,k,l)]);
                            if(0) /* TODO Le fichier de font ne marche pas */
                            {
                                MLV_draw_text_with_font(
                                    tmp_slot_X + (tmp_slot_Width/2), 
                                    tmp_slot_Y + (tmp_slot_Height/2), 
                                    tmp_slot_char, 
                                    font,
                                    num_color
                                    );
                            }
                            else
                            {
                                MLV_draw_text( 
                                    tmp_slot_X + (tmp_slot_Width/2)-5, 
                                    tmp_slot_Y + (tmp_slot_Height/2)-5, 
                                    tmp_slot_char, 
                                    num_color);
                            }
                        }
                    }

        /* Contours plus épais pour les cellules de 9x9*/
        for(i = 0; i < 3; i++)
            for(j = 0; j < 3; j++)
                MLV_draw_rectangle(
                MARGIN_LEFT-1 + i*SLOT_SIZE*3, 
                MARGIN_TOP-1 + j*SLOT_SIZE*3, 
                SLOT_SIZE*3+1, 
                SLOT_SIZE*3+1, 
                BLACK);



        /*--------Section dessin de la grille de séléction--------*/
        if(!currentSelectedSlotIsEmpty()) /* On vérifie que le joueur a séléctionné une case*/
        {
            /* On met en surbrillance la case séléctionnée*/
            MLV_draw_rectangle(tmp_slot_sur_X, tmp_slot_sur_Y, tmp_slot_sur_Width, tmp_slot_sur_Height, ORANGE);
            MLV_draw_rectangle(tmp_slot_sur_X-1, tmp_slot_sur_Y-1, tmp_slot_sur_Width+2, tmp_slot_sur_Height+2, ORANGE);
            
            
            /* On affiche la grille de séléction*/

            k = 1; /*Compteur pour afficher les choix*/
            for(j = 0; j < 3; j++)
                for(i = 0; i < 3; i++)
                {
                    /* Dessin des cases */
                    MLV_draw_rectangle(
                        MARGIN_LEFT*2 + SLOT_SIZE*9 + i*SLOT_SIZE,
                        MARGIN_TOP + SLOT_SIZE*3 + j*SLOT_SIZE, 
                        SLOT_SIZE, 
                        SLOT_SIZE, 
                        BLACK);

                    sprintf(tmp_slot_char, "%d", k);
                    if(0) /* TODO Le fichier de font ne marche pas */
                        {
                            MLV_draw_text_with_font(
                                 MARGIN_LEFT*2 + SLOT_SIZE*9 + i*SLOT_SIZE + (SLOT_SIZE/2)-5, 
                                MARGIN_TOP + SLOT_SIZE*3 + j*SLOT_SIZE + (SLOT_SIZE/2)-5, 
                                tmp_slot_char, 
                                font,
                                BLACK
                                );
                        }
                        else
                        {
                            MLV_draw_text( 
                                MARGIN_LEFT*2 + SLOT_SIZE*9 + i*SLOT_SIZE + (SLOT_SIZE/2)-5, 
                                MARGIN_TOP + SLOT_SIZE*3 + j*SLOT_SIZE + (SLOT_SIZE/2)-5, 
                                tmp_slot_char, 
                                BLACK);
                        }
                    k++;
                }

            /* Dessin du contour de la grille*/
            MLV_draw_rectangle(MARGIN_LEFT*2 + SLOT_SIZE*9, MARGIN_TOP + SLOT_SIZE*3, SLOT_SIZE*3, SLOT_SIZE*3, ORANGE);
            MLV_draw_rectangle(MARGIN_LEFT*2 + SLOT_SIZE*9 -1, MARGIN_TOP + SLOT_SIZE*3 -1, SLOT_SIZE*3+2, SLOT_SIZE*3+2, ORANGE);

        }






        /* On actualise l'affichage avec les dernières modifications*/
        MLV_actualise_window();
    }

    /* On libère la mémoire prise par la font et on finit le thread*/
    MLV_free_font(font);
    pthread_exit(NULL);
    return 0;
}

/* Fonction permettant de dire que l'utilisateur n'a aucune séléction*/
void emptyCurrentSelectedSlot()
{
    currentSelectedSlot.x1 = -1;
    currentSelectedSlot.y1 = -1;
    currentSelectedSlot.x2 = -1;
    currentSelectedSlot.y2 = -1;
}

/* Fonction permettant de vérifer si l'utilisateur a séléctionné une case */
int currentSelectedSlotIsEmpty()
{
    if(currentSelectedSlot.x1 == -1 || currentSelectedSlot.y1 == -1 || currentSelectedSlot.x2 == -1 || currentSelectedSlot.y2 == -1)
        return TRUE;
    return FALSE;
}


