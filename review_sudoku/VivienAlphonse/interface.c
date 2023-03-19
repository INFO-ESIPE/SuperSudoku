#include "interface.h"

#include "MLV/MLV_all.h"
#include "stdio.h"
#include "stdlib.h"

void prepare_grid_properties(struct Grid_properties *grid, int width_of_window, int height_of_window, char *title, int size_of_grid)
{

    int width_for_main_box = height_of_window > (width_of_window * 0.7) ? width_of_window * 0.7 : height_of_window; /* minimum 30% of the width_of_window is left for the second box */
    int margin = width_for_main_box * 0.05;                                                                         /* 5% of the width the grid is the margin size */
    int cell_size = (width_for_main_box - 2 * margin) / size_of_grid;

    grid->title = title;
    grid->width = width_for_main_box;
    grid->size = size_of_grid;
    grid->cell_size = cell_size;
    grid->margin = margin;
}

void init_interface(struct Grid_properties grid)
{
    MLV_draw_text(grid.margin, grid.margin / 2, grid.title, MLV_COLOR_GREEN);
    int i;
    for (i = 0; i <= grid.size; i++)
    {
        MLV_draw_line(grid.margin + i * grid.cell_size, grid.margin, grid.margin + i * grid.cell_size, grid.margin + grid.size * grid.cell_size, MLV_COLOR_WHEAT1); /* vertical lines */
        MLV_draw_line(grid.margin, grid.margin + i * grid.cell_size, grid.margin + grid.size * grid.cell_size, grid.margin + i * grid.cell_size, MLV_COLOR_WHEAT1); /* horizontal lines */
    }
    MLV_actualise_window();
}

void init_grid(Board board, struct Grid_properties grid)
{
    init_interface(grid);
    int grid_line, grid_column;
    for (grid_line = 0; grid_line < grid.size; grid_line++)
    {
        for (grid_column = 0; grid_column < grid.size; grid_column++)
        {

            /* preparing text */
            char *text = malloc(sizeof(char) * 2);              /* using malloc to reduce the risk of stack overflow, using char size of 2 as the number will allways be 1 digit */
            sprintf(text, "%d", board[grid_line][grid_column]); /* converting int to char */

            fill_case(grid, grid_line, grid_column, text, MLV_COLOR_WHITE);
            /* freeing */
            free(text);
        }
    }
    MLV_actualise_window();
}

int pixel_coordinates_to_grid_coordinates(int x, int y, struct Grid_properties grid, int *grid_line, int *grid_column)
{
    if (x < grid.margin || x > grid.margin + grid.size * grid.cell_size || y < grid.margin || y > grid.margin + grid.size * grid.cell_size)
    {
        return 1;
    }
    *grid_column = (x - grid.margin) / grid.cell_size;
    *grid_line = (y - grid.margin) / grid.cell_size;
    return 0;
}

int grid_coordinates_to_pixel_coordinates(int grid_line, int grid_column, struct Grid_properties grid, int *x, int *y)
{
    if (grid_line < 0 || grid_line >= grid.size || grid_column < 0 || grid_column >= grid.size)
    {
        return 1;
    }
    int text_width, text_height;
    MLV_get_size_of_text("X", &text_width, &text_height, NULL);
    *x = grid.margin + grid_column * grid.cell_size + (grid.cell_size - text_width) / 2;
    *y = grid.margin + grid_line * grid.cell_size + (grid.cell_size - text_height) / 2;
    return 0;
}

int show_value_selector_grid(struct Grid_properties grid, int *unavailable_values)
{
    int width_value_selector_grid = (grid.width / 7) * 3;
    int margin_left_or_right = width_value_selector_grid * 0.05;
    int cell_size = (width_value_selector_grid - 2 * margin_left_or_right) / 3;
    int margin_top = grid.width / 2 - (cell_size * 3) / 2; /* to center the grid */

    MLV_draw_filled_rectangle(grid.width, 0, width_value_selector_grid, grid.width, MLV_COLOR_BLACK); /* to make sure there is no value selector grid left from old function call */
    int i;
    for (i = 0; i <= 3; i++)
    {
        MLV_draw_line(grid.width + margin_left_or_right + i * cell_size, margin_top, grid.width + margin_left_or_right + i * cell_size, margin_top + 3 * cell_size, MLV_COLOR_WHEAT1); /* vertical lines */
        MLV_draw_line(grid.width + margin_left_or_right, margin_top + i * cell_size, grid.width + margin_left_or_right + 3 * cell_size, margin_top + i * cell_size, MLV_COLOR_WHEAT1); /* horizontal lines */
    }
    int number_iterator;
    int x, y;

    int color_of_text = MLV_COLOR_GREY;
    for (number_iterator = 1; number_iterator <= 9; number_iterator++)
    {
        /* checking if the value is unavailable */
        if (unavailable_values != NULL)
        {
            if (unavailable_values[number_iterator] == 1) /* 1 means that the value is available */
            {
                color_of_text = MLV_COLOR_DARK_RED;
            }
            else
            {
                color_of_text = MLV_COLOR_LIGHT_GREEN;
            }
        }

        /* preparing text */
        char *text = malloc(sizeof(char) * 2); /* using malloc to reduce the risk of stack overflow, using char size of 2 as the number_iterator will allways be 1 digit */
        sprintf(text, "%d", number_iterator);  /* converting int to char */
        int text_width, text_height;
        MLV_get_size_of_text(text, &text_width, &text_height, NULL);
        x = grid.width + margin_left_or_right + (number_iterator - 1) % 3 * cell_size + (cell_size - text_width) / 2;
        y = margin_top + (number_iterator - 1) / 3 * cell_size + (cell_size - text_height) / 2;

        /* drawing */
        MLV_draw_text(x, y, text, color_of_text);

        /* freeing */
        free(text);
    }
    MLV_actualise_window();
    MLV_wait_mouse(&x, &y);
    int quit = 0;
    int return_value = 0;

    while (!quit)
    {

        if (are_coordinates_inside_the_value_selector_grid(x, y, grid, margin_left_or_right, margin_top, cell_size))
        {
            return_value = (x - grid.width - margin_left_or_right) / cell_size + 1 + 3 * ((y - margin_top) / cell_size);
            quit = 1;
        }
        else if (are_coordinates_outside_the_grids(x, y, grid, width_value_selector_grid, margin_left_or_right, margin_top, cell_size))
        {
            quit = 1;
        }
        else
        {
            quit = 1;
        }
    }
    /* cleaning the value selector grid */
    MLV_draw_filled_rectangle(grid.width, 0, width_value_selector_grid, grid.width, MLV_COLOR_BLACK);

    return return_value;
}

int are_coordinates_outside_the_grids(int x, int y, struct Grid_properties grid, int width_value_selector_grid, int margin_left_or_right, int margin_top, int cell_size_of_value_selector_grid)
{
    /* defining the conditions to check if the user clicked outside the grids */
    int is_outside_the_main_grid = x <= grid.margin || y <= grid.margin || y >= (grid.width - grid.margin);
    int is_between_the_grids = ((x <= (grid.width + margin_left_or_right)) && (x >= (grid.width - grid.margin)));
    int is_outside_the_value_selector_grid = x >= grid.width + width_value_selector_grid - margin_left_or_right ||
                                             (x >= grid.width + margin_left_or_right && x <= grid.width + width_value_selector_grid - margin_left_or_right && (y <= margin_top || y >= margin_top + 3 * cell_size_of_value_selector_grid));

    int is_outside_the_grids = is_outside_the_main_grid || is_between_the_grids || is_outside_the_value_selector_grid;
    return is_outside_the_grids;
}

int are_coordinates_inside_the_value_selector_grid(int x, int y, struct Grid_properties grid, int margin_left_or_right, int margin_top, int cell_size_of_value_selector_grid)
{
    /* defining the conditions to check if the user clicked inside the value selector grid */
    int is_inside_the_value_selector_grid = x >= grid.width + margin_left_or_right && x <= grid.width + margin_left_or_right + 3 * cell_size_of_value_selector_grid && y >= margin_top && y <= margin_top + 3 * cell_size_of_value_selector_grid;
    return is_inside_the_value_selector_grid;
}

int fill_case(struct Grid_properties grid, int grid_line, int grid_column, char *text, int text_color)
{
    if (text_color == 0)
    {
        text_color = MLV_COLOR_GREEN;
    }
    if (*text == '0')
    {
        int x, y;
        grid_coordinates_to_pixel_coordinates(grid_line, grid_column, grid, &x, &y);

        MLV_draw_filled_rectangle(x, y, grid.cell_size / 2, grid.cell_size / 2, MLV_COLOR_BLACK); /* cleaning the cell */
        return 0;
    }
    int cell_size = (grid.width - 2 * grid.margin) / grid.size;
    int text_width, text_height;
    MLV_get_size_of_text(text, &text_width, &text_height, NULL);
    int x = grid.margin + grid_column * cell_size + (cell_size - text_width) / 2;
    int y = grid.margin + grid_line * cell_size + (cell_size - text_height) / 2;
    MLV_draw_text(x, y, text, text_color);
    MLV_actualise_window();
    return 0;
}

void game_over(struct Grid_properties grid, int game_result)
{
    int x, y;
    int text_width, text_height;
    char *text;
    int text_color = MLV_COLOR_GREEN;
    if (game_result == 0)
    {
        text = "You won !!!";
    }
    else
    {
        text = "You lost :(";
        text_color = MLV_COLOR_RED;
    }
    MLV_get_size_of_text(text, &text_width, &text_height, NULL);
    x = grid.width - text_width - grid.margin; /* to align the text to the right of the grid */
    y = grid.margin / 2;
    MLV_draw_text(x, y, text, text_color);
    MLV_actualise_window();
    MLV_wait_mouse(&x, &y);
}