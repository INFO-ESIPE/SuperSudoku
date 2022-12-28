/*
	Programmation C - TP7
	Max Ducoudré - INFO1
    Fonctions permettant de gérer la partie graphique de la grille
*/

#include <stdio.h>
#include <stdlib.h>

#include "../headers/grid_frame.h"


int drawNumSelect = FALSE; /* Variable permettant de dire si oui ou non on dessine la grille de séléction de numéro */
int action = ACTION_EMPTY; /*Représente l'action en cours sur une partie de sudoku*/
int drawScores = FALSE;/*Variable permettant de dire si on dessine le tableau des scores*/

/*Bouttons du menu*/
struct MenuButton scoreButton, autoresolveButton, restartButton, exitButton;


/* Fonction permettant de générer la fenêtre contenant la grille de sudoku*/
void generateGridFrame(struct SuperSudoku grids)
{
    MLV_create_window(GAME_NAME,  "resources/Sudoku.png", WIN_WIDTH, WIN_HEIGHT); /* Création de la fenêtre*/
    startListenMouse(grids);  /*Ecoute le clique de la souris*/
    startDrawUpdate(grids); /* On actualise la grid en temps réel en fonction de la modification des données dans stockés dans SuperSoduku*/

    /* On boucle jusqu'à la fin du jeux
    Cette boucle nous permet de récupérer l'action du joueur*/
    /*
    while (action != ACTION_END)
    {
        if(action == ACTION_EMPTY)
        {
            MLV_wait_milliseconds(WAIT_TIME_MILLISEC);

            
            if(isGridFull(grids.gameGrid)) {}
            
        }
    }
    */
}

/*
    Prend en argument des coordonées x y sur la fenêtre et modifie selected_value avec la valeur choisie par l'utilisateur
    Renvoi 1 si la fonction a réussie et 0 sinon
 */
int getSlotChoice(int mouseX, int mouseY, int* selected_value)
{
    int i,j, k;
    if(slotIsEmpty(getCurrentSelectedSlot())) return FALSE;
    
    k = 1;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
        {
            if(
                mouseX > MARGIN_LEFT*2 + SLOT_SIZE*9 + (j*SLOT_SIZE) && mouseX < MARGIN_LEFT*2 + SLOT_SIZE*9 + ((j+1)*SLOT_SIZE) &&
                mouseY > MARGIN_TOP + SLOT_SIZE*3 + (i*SLOT_SIZE) && mouseY < MARGIN_TOP + SLOT_SIZE*3 + ((i+1)*SLOT_SIZE)
            ) {
                *selected_value = k;
                return TRUE;
            }
            if(mouseX > MARGIN_LEFT*2 + SLOT_SIZE*10 -1 &&  mouseX < MARGIN_LEFT*2 + SLOT_SIZE*10 -1 + SLOT_SIZE+2 &&
               mouseY >MARGIN_TOP+ SLOT_SIZE*2 - 10 -1 &&  mouseY < MARGIN_TOP+ SLOT_SIZE*2 - 10 -1 + SLOT_SIZE+2
            ) {
                *selected_value = 0;
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

/*Fonction commençant le thread d'actualisation de l'affichage*/
void startDrawUpdate(struct SuperSudoku grids)
{
    /*pthread_t threadDrawID;*/
    /*pthread_create(&threadDrawID, NULL, &updateDraw, &grids);*/
    updateDraw(grids);
}

/*Cette fonction met à jour l'affichage en fonction des données envoyé dedans*/
int updateDraw(struct SuperSudoku grids)
{
    /* Données de la grille*/
    /*struct SuperSudoku *grids = args;*/
    SudokuGrid gameGrid = grids.gameGrid;
    SudokuGrid forbiddenGrid = grids.forbiddenGrid;
    struct SlotLocation currentSelectedSlot = getCurrentSelectedSlot();
    struct SlotLocation currentOverSlot; 

    /* Valeurs temporaire pour remplir le tableau*/
    int i, j, k, l;
    int tmp_slot_X, tmp_slot_Y, tmp_slot_Width, tmp_slot_Height;
    char tmp_slot_char[255];
    MLV_Color num_color = BLACK;
    int currentOverSelectorSlot;

    /* Valeurs pour la surbrillance de la case séléctionnée*/
    int tmp_slot_sur_X, tmp_slot_sur_Y, tmp_slot_sur_Width, tmp_slot_sur_Height;

    /* Chargement d'une nouvelle police d'écriture*/
    MLV_Font* font = MLV_load_font("resources/Georgia.ttf" , 20);

    /*Variable pour le dessin du timer*/
    char timer_buffer[255];

    /*Variable pour le dessin du tableau du score*/
    char score_buffer[255];

    /*Manage score*/
    struct ScoreData scores[255];
    scoreButton.x = MARGIN_LEFT + (NB_SLOT_SUBGRID+1) * SLOT_SIZE;  
    scoreButton.y = MARGIN_TOP + (NB_SLOT_SUBGRID-2) * SLOT_SIZE;  
    scoreButton.width = SLOT_SIZE*2;
    scoreButton.height = SLOT_SIZE*0.8;
    scoreButton.color = BLACK;
    scoreButton.over_color = ORANGE;
    scoreButton.text = "High scores";
    scoreButton.font = font;

    autoresolveButton = scoreButton;
    autoresolveButton.x += SLOT_SIZE*2 + 10;
    autoresolveButton.text = "Auto resolve";

    restartButton = scoreButton;
    restartButton.y += SLOT_SIZE*0.8 + 10;
    restartButton.text = "Restart";

    exitButton = scoreButton;
    exitButton.x += SLOT_SIZE*2 + 10;
    exitButton.y += SLOT_SIZE*0.8 + 10;
    exitButton.text = "Exit";






    /* Actualisation de l'affichage en temps réel avec les données des grilles */
    while(1 && action != ACTION_END)
    {
        MLV_wait_milliseconds(13);
        currentSelectedSlot = getCurrentSelectedSlot();

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

                        /*Ajout de la valeur dans la case*/
                        if(gameGrid[gridOffset(i,j,k,l)] > 0 && gameGrid[gridOffset(i,j,k,l)] <=9)
                        {
                            if(forbiddenGrid[gridOffset(i,j,k,l)] == 1) num_color = GRAY;
                            else num_color = BLACK;

                            sprintf(tmp_slot_char, "%d", gameGrid[gridOffset(i,j,k,l)]);
                            MLV_draw_text_with_font(
                                tmp_slot_X + (tmp_slot_Width/2) - 8, 
                                tmp_slot_Y + (tmp_slot_Height/2) - 8, 
                                tmp_slot_char, 
                                font,
                                num_color
                                );
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

        /*On met en surbrillance les cases survolés*/
        if(getCurrentOverSlotLocation(&currentOverSlot) &&  /*On vérifie si on survole bien une case  */
        forbiddenGrid[gridOffset(currentOverSlot.x1, currentOverSlot.y1, currentOverSlot.x2, currentOverSlot.y2)] == 0) /*Et on vérifie si c'est une case jouable*/
        {
            /*printf("%d,%d,%d,%d\n",currentOverSlot.x1, currentOverSlot.y1, currentOverSlot.x2, currentOverSlot.y2);*/
            /*On met en surbrillance les lignes & les colones*/
            for(i = 0; i < NB_SUBGRID/3; i++) 
                for(j = 0; j < NB_SUBGRID/3; j++) 
                    for(k = 0; k < NB_SLOT_SUBGRID/3; k++)
                        for(l = 0; l < NB_SLOT_SUBGRID/3; l++) {
                            if((currentOverSlot.x1 == i && currentOverSlot.x2 == k) ||
                               (currentOverSlot.y1 == j && currentOverSlot.y2 == l))
                            {
                                MLV_draw_rectangle(
                                    MARGIN_LEFT + (j*SLOT_SIZE*3) + (l*SLOT_SIZE),
                                    MARGIN_TOP + (i*SLOT_SIZE*3) + (k*SLOT_SIZE),
                                    SLOT_SIZE+1,
                                    SLOT_SIZE+1, 
                                    GREEN);

                            }
                    }
            /* On met en surbrillance la case survolée*/
            MLV_draw_rectangle(
                MARGIN_LEFT + (currentOverSlot.y1*SLOT_SIZE*3) + (currentOverSlot.y2*SLOT_SIZE),
                MARGIN_TOP + (currentOverSlot.x1*SLOT_SIZE*3) + (currentOverSlot.x2*SLOT_SIZE), 
                SLOT_SIZE+1, 
                SLOT_SIZE+1, 
                GREEN);

            MLV_draw_rectangle(
                MARGIN_LEFT + (currentOverSlot.y1*SLOT_SIZE*3) + (currentOverSlot.y2*SLOT_SIZE)-1,
                MARGIN_TOP + (currentOverSlot.x1*SLOT_SIZE*3) + (currentOverSlot.x2*SLOT_SIZE)-1, 
                SLOT_SIZE+3, 
                SLOT_SIZE+3, 
                GREEN);
        }

        /*--------Section dessin de la grille de séléction--------*/
        if(!slotIsEmpty(currentSelectedSlot) && !drawScores) /* On vérifie que le joueur a séléctionné une case*/
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
                        
                    MLV_draw_text_with_font(
                            MARGIN_LEFT*2 + SLOT_SIZE*9 + i*SLOT_SIZE + (SLOT_SIZE/2)-5, 
                        MARGIN_TOP + SLOT_SIZE*3 + j*SLOT_SIZE + (SLOT_SIZE/2)-5, 
                        tmp_slot_char, 
                        font,
                        BLACK
                        );

                    k++;
                }

            /* Dessin du contour de la grille*/
            MLV_draw_rectangle(MARGIN_LEFT*2 + SLOT_SIZE*9, MARGIN_TOP + SLOT_SIZE*3, SLOT_SIZE*3, SLOT_SIZE*3, ORANGE);
            MLV_draw_rectangle(MARGIN_LEFT*2 + SLOT_SIZE*9 -1, MARGIN_TOP + SLOT_SIZE*3 -1, SLOT_SIZE*3+2, SLOT_SIZE*3+2, ORANGE);

            /*Dessin du bouton de cancel*/
            MLV_draw_rectangle(
                MARGIN_LEFT*2 + SLOT_SIZE*10, 
                MARGIN_TOP+ SLOT_SIZE*2 - 10, 
                SLOT_SIZE,
                SLOT_SIZE, 
                RED);
            MLV_draw_rectangle(
                MARGIN_LEFT*2 + SLOT_SIZE*10 -1, 
                MARGIN_TOP+ SLOT_SIZE*2 - 10 -1, 
                SLOT_SIZE+2,
                SLOT_SIZE+2, 
                RED);
            MLV_draw_text( 
                MARGIN_LEFT*2 + SLOT_SIZE*10 -1 + SLOT_SIZE/2 - 5, 
                MARGIN_TOP+ SLOT_SIZE*2 - 10 -1 + SLOT_SIZE/2 - 5, 
                "X",
                RED);

            /*On met en surbrillance le bouton survolé du selecteur*/
            currentOverSelectorSlot = getCurrentOverSelectorSlot();
            if(currentOverSelectorSlot != -1)
            {
                for(j = 0; j < 3; j++)
                    for(i = 0; i < 3; i++)
                    {
                        if(j+i*3 == currentOverSelectorSlot-1)
                        {
                            if(isSlotCompatibleInGrid(gameGrid, currentSelectedSlot.x1, currentSelectedSlot.y1, currentSelectedSlot.x2, currentSelectedSlot.y2, currentOverSelectorSlot))
                                num_color = GREEN;
                            else 
                                num_color = RED;

                            MLV_draw_rectangle(
                                MARGIN_LEFT*2 + SLOT_SIZE*9 + j*SLOT_SIZE,
                                MARGIN_TOP + SLOT_SIZE*3 + i*SLOT_SIZE, 
                                SLOT_SIZE, 
                                SLOT_SIZE, 
                            num_color);
                            MLV_draw_rectangle(
                                MARGIN_LEFT*2 + SLOT_SIZE*9 + j*SLOT_SIZE-1,
                                MARGIN_TOP + SLOT_SIZE*3 + i*SLOT_SIZE-1, 
                                SLOT_SIZE+2, 
                                SLOT_SIZE+2, 
                            num_color);
                        }
                    }
            }
        }


        /* Dessin du timer */
        getTimerString(timer_buffer);
        MLV_draw_text_with_font(
            MARGIN_LEFT, 
            MARGIN_TOP/4, 
            timer_buffer, 
            font,
            BLACK);



        /*Dessin du menu*/
        /*Scores/autoresolve/restart/fin*/
        drawButton(scoreButton);
        drawButton(autoresolveButton);
        drawButton(exitButton);
        drawButton(restartButton);


        /*Dessin du tableau des scores*/
        if(drawScores)
        {   
            readScore(scores, SCORE_TO_DISPLAY);
            MLV_draw_text_with_font(
                MARGIN_LEFT + SLOT_SIZE*10, 
                MARGIN_TOP, 
                "High scores", 
                font,
                BLACK);

            for(i = 0; scores[i].time != -1; i++)
            {
                /*printf("%d\n", scores[i].time);*/
                sprintf(score_buffer, "%d:%d - %s (%s)", (scores[i].time/60), (scores[i].time%60), scores[i].grid, scores[i].date);
                MLV_draw_text_with_font(
                    MARGIN_LEFT + SLOT_SIZE*10, 
                    MARGIN_TOP+ ((i+1)*30), 
                    score_buffer, 
                    font,
                    BLACK);
            }
            

            

                
        }


        /* On actualise l'affichage avec les dernières modifications*/
        MLV_actualise_window();
    }



    /*Dessin qu'à la fin de la partie*/
    if(isGridFull(gameGrid))
    {
        
    }

    /* On libère la mémoire prise par la font et on finit le thread*/
    /*MLV_free_font(font);*/
    pthread_exit(NULL);
    return 0;
}


/*Function permettant de dessiner un bouton*/
void drawButton(struct MenuButton menuButton)
{

    int mouseX;
    int mouseY;
    MLV_Color draw_color = menuButton.color;

    MLV_get_mouse_position(&mouseX, &mouseY);
    
    if(mouseX > menuButton.x && mouseX < menuButton.x+menuButton.width &&
       mouseY  > menuButton.y && mouseY < menuButton.y+menuButton.height)
       draw_color = menuButton.over_color;

    MLV_draw_rectangle(
        menuButton.x,
        menuButton.y, 
        menuButton.width, 
        menuButton.height, 
        draw_color);

    MLV_draw_text_with_font(
        menuButton.x+5, 
        menuButton.y+menuButton.height/4, 
        menuButton.text, 
        menuButton.font,
        menuButton.color);
    
}

/*Fonction permettant de récupérer l'action en cours sur la fenêtre*/
int getCurrentAction()
{
    return action;
}

/*Fonction permettant de libérer la mémoire utilisée par la fenêtre*/
void freeFrame()
{
    action = ACTION_END;
    freeListener();
    MLV_free_window();
}


struct MenuButton getMenuButtons(int button_id)
{
    if(button_id == 0) return scoreButton;
    else if(button_id == 1) return autoresolveButton;
    else if(button_id == 2) return exitButton;
    return restartButton;
    
}

void setDrawScore(int rawScoresStatus)
{
    drawScores = rawScoresStatus;
}