#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "sudoku.h"
#include "in_out.h"

int main(int argc, char *argv[])
{
  Board B;
  Board exemple;
  fread_board(argv[1], B, exemple);
  create_windows();
  clear_window();
  print_grid(B, exemple);
  actualise_window();
  while (is_grid_correct(B) != 1)
  {
    resolve_sudoku(B, exemple);
    clear_window();
    print_grid(B, exemple);
    actualise_window();
  }
  game_completed();
  return 0;
}

/* améliorer fonction test valeur */
/* modifier affichage */
