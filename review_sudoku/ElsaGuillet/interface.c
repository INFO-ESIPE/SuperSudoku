#include <MLV/MLV_all.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "interface.h"
#include "sudoku.h"

void create_windows(void)
{
  MLV_create_window("Sudoku", NULL, WIDTH_WINDOWS_PIX, HEIGHT_WINDOWS_PIX);
}

void free_windows(void)
{
  MLV_free_window();
}

void actualise_window(void)
{
  MLV_actualise_window();
}

void clear_window(void)
{
  MLV_clear_window(MLV_COLOR_WHITE);
}

void wait_window(int sec)
{
  MLV_wait_seconds(sec);
}

void game_completed(void)
{
  const char *text_box = "BRAVO, VOUS AVEZ GAGNE!";
  int width_box = 0, height_box = 0, size_interligne = 25;
  MLV_get_size_of_adapted_text_box(
      text_box,
      size_interligne,
      &width_box, &height_box);
  int positionBoxX = (800 - width_box) / 2, positionBoxY = 250;
  MLV_draw_adapted_text_box(
      positionBoxX, positionBoxY,
      text_box,
      size_interligne,
      MLV_COLOR_GOLD, MLV_COLOR_GOLD, MLV_COLOR_WHITE,
      MLV_TEXT_CENTER);

  const char *text_boxQuit = "quitter le jeu";
  int width_boxQuit = 0, height_boxQuit = 0, size_interligneQuit = 15;
  MLV_get_size_of_adapted_text_box(
      text_boxQuit,
      size_interligneQuit,
      &width_boxQuit, &height_boxQuit);
  int positionBoxXQuit = (800 - width_boxQuit) / 2, positionBoxYQuit = 350;
  MLV_draw_adapted_text_box(
      positionBoxXQuit, positionBoxYQuit,
      text_boxQuit,
      size_interligneQuit,
      MLV_COLOR_RED, MLV_COLOR_RED, MLV_COLOR_WHITE,
      MLV_TEXT_CENTER);

  actualise_window();
  while (1 == 1)
  {
    quit_game(width_boxQuit, height_boxQuit, positionBoxXQuit, positionBoxYQuit);
  }
}

void quit_game(int width, int height, int x, int y)
{
  int xs, ys;
  MLV_wait_mouse(&xs, &ys);
  if (xs > x && xs < (x + width) && ys > y && ys < (y + height))
  {
    free_windows();
  }
}

void print_grid(Board grid, Board exemple)
{
  int i, j;
  /* Dessin lignes et colonnes*/
  MLV_draw_line(50, 50, 500, 50, MLV_COLOR_BLACK);
  for (i = 0; i <= 9; i++)
  {
    MLV_draw_line(50, (50 + 50 * i), 500, (50 + 50 * i), MLV_COLOR_BLACK);
  }
  MLV_draw_line(50, 50, 50, 500, MLV_COLOR_BLACK);
  for (j = 0; j <= 9; j++)
  {
    MLV_draw_line((50 + 50 * j), 50, (50 + 50 * j), 500, MLV_COLOR_BLACK);
  }
  int t=0;
  for(i=0;i<3;i++){
  	for(j=0;j<3;j++){
  		if(t%2!=0){
  			MLV_draw_filled_rectangle(50+(i*150),50+(j*150),150,150, MLV_rgba(0, 0, 0, 30));
  		}
  		t++;
  	}
  }

  /* Affichage des chiffres de la grille */
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      if (grid[i][j] != 0 && exemple[i][j] != 0)
      {
        char chiffre[] = "0";
        chiffre[0] = grid[i][j] + '0';
        MLV_draw_text((50 + 50 * j + 22), (50 + 50 * i + 20), chiffre, MLV_COLOR_BLUE1);
      }
      else if (grid[i][j] != 0 && exemple[i][j] == 0)
      {
        char chiffre[] = "0";
        chiffre[0] = grid[i][j] + '0';
        MLV_draw_text((50 + 50 * j + 22), (50 + 50 * i + 20), chiffre, MLV_COLOR_BLACK);
      }
    }
  }
}

/* Clic case vide */
void resolve_sudoku(Board grid, Board exemple)
{
  int xs, ys, x, y;
  MLV_wait_mouse(&xs, &ys);
  if (50 < xs && xs < 500 && 50 < ys && ys < 500)
  {
    /*cases dans la grille de base*/
    y = (xs - 50) / 50;
    x = (ys - 50) / 50;

    if (exemple[x][y] == 0)
    {
      print_numbers();
      color_case(x, y);
      actualise_window();
      wait_number(x, y, grid);
    }
  }
}

/* Colorer en vert la case en cours */
void color_case(int x, int y)
{
  MLV_draw_filled_rectangle(50 + 50 * y, 50 + 50 * x, 50, 50, MLV_rgba(50, 205, 50, 100));
  actualise_window();
}

/* Affichage des nombres à ajouter */
void print_numbers()
{
  int i, j;
  MLV_draw_line(600, 200, 750, 200, MLV_COLOR_BLACK);
  for (i = 0; i <= 3; i++)
  {
    MLV_draw_line(600, (200 + 50 * i), 750, (200 + 50 * i), MLV_COLOR_BLACK);
  }

  MLV_draw_line(600, 200, 600, 350, MLV_COLOR_BLACK);
  for (j = 0; j <= 3; j++)
  {
    MLV_draw_line((600 + 50 * j), 200, (600 + 50 * j), 350, MLV_COLOR_BLACK);
  }

  for (i = 1; i <= 3; i++)
  {
    for (j = 1; j <= 3; j++)
    {
      char chiffre[] = "0";
      chiffre[0] = (j + 3 * (i - 1)) + '0';
      MLV_draw_text((600 + 50 * (j - 1) + 20), (200 + 50 * (i - 1) + 20), chiffre, MLV_COLOR_BLACK);
    }
  }
}

/* Clic chiffres */
void wait_number(int x, int y, Board grid)
{
  int xs, ys;
  int nb = 0;
  MLV_wait_mouse(&xs, &ys);
  if (600 < xs && xs < 750 && 200 < ys && ys < 350)
  {
    nb = (((ys - 200) / 50) * 3 + (((xs - 600) / 50) +1));
  }
  else
  {
    clear_window();
    return;
  }
	
  if (is_value_correct(grid, x, y, nb) == 1)
  {
    grid[x][y] = nb;
    MLV_clear_window(MLV_COLOR_WHITE);
    return;
  }
  MLV_draw_filled_rectangle(50 + 50 * y, 50 + 50 * x, 50, 50, MLV_COLOR_RED1);
  actualise_window();
  wait_window(1);
  /*MLV_draw_filled_rectangle(50 + 50 * y, 50 + 50 * x, 50, 50, MLV_COLOR_WHITE);*/
  MLV_clear_window(MLV_COLOR_WHITE);
}
