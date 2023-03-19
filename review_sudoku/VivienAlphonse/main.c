#include "in_out.h"
#include "interface.h"
#include "sudoku.h"

#include "MLV/MLV_all.h"
#include "string.h"

int main(int argc, char *argv[])
{
    if (SIZE_OF_GRID != 6 && SIZE_OF_GRID != 9)
    {
        printf("SIZE_OF_GRID must be 6 or 9\n");
        return 1;
    }
    if (!argv[1])
    {
        argv[1] = "data/grid1.txt"; /* if no file is given as argument, we use the grid1.txt file in data folder as default board */
    }
    Board base_board;
    fread_board(argv[1], base_board, SIZE_OF_GRID);

    MLV_create_window(TITLE, NULL, WIDTH, HEIGHT);
    MLV_Keyboard_button key;

    struct Grid_properties grid;
    prepare_grid_properties(&grid, WIDTH, HEIGHT, TITLE, SIZE_OF_GRID);
    init_grid(base_board, grid);

    int grid_line, grid_column;
    Board current_board;
    memcpy(&current_board, &base_board, sizeof(Board)); /* coping the base board to the current board to be able to modify it */
    int quit = 0;
    while (!quit)
    {
        int x, y;
        MLV_wait_keyboard_or_mouse(&key, NULL, NULL, &x, &y);
        if (key == MLV_KEYBOARD_ESCAPE)
        {
            quit = 1;
            continue;
        }
        if (!pixel_coordinates_to_grid_coordinates(x, y, grid, &grid_line, &grid_column) && base_board[grid_line][grid_column] == 0) /* if the click is not out of the grid and the cell is empty */
        {
            int result = playCase(&current_board, grid, grid_line, grid_column, SHOW_RIGHT_ANSWERS_IN_VALUE_SELECTOR_GRID);
            if (result == 1)
            {
                game_over(grid, 1); /* lost */
                quit = 1;
                continue;
            }
            else if (result == 0 && is_board_full(current_board, grid.size) == 0)
            {
                game_over(grid, 0); /* won */
                quit = 1;
                continue;
            }
        }
        MLV_actualise_window();
    }
    MLV_free_window();
    return 0;
}