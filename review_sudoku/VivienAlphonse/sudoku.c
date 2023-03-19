#include "MLV/MLV_all.h"
#include "sudoku.h"
int playCase(Board *current_board, struct Grid_properties grid, int grid_line, int grid_column, int show_right_answers)
{
    fill_case(grid, grid_line, grid_column, "0", 0);
    fill_case(grid, grid_line, grid_column, "?", MLV_COLOR_BLUE);

    int *unavailable_values = find_already_used_values(*current_board, grid_line, grid_column, grid.size);
    int selected_value;
    if (show_right_answers == 0) /* if it is enabled */
    {
        selected_value = show_value_selector_grid(grid, unavailable_values);
    }
    else
    {
        selected_value = show_value_selector_grid(grid, NULL);
    }

    if (selected_value != 0)
    {

        /* condition where the selected value is already used in the current case OR the selected value is acceptable */
        if (((*current_board)[grid_line][grid_column] == selected_value) || (unavailable_values[selected_value] != 1)) /* here we are calling the current board like this `(*current_board)` as current_board is a pointer, so we are accessing the value of the pointer */
        {
            char text[2];
            sprintf(text, "%d", selected_value);
            fill_case(grid, grid_line, grid_column, "0", 0);
            fill_case(grid, grid_line, grid_column, text, 0);
            (*current_board)[grid_line][grid_column] = selected_value;
            return 0;
        }

        /* wrong value condition */
        else
        {
            char text[2];
            sprintf(text, "%d", selected_value);
            fill_case(grid, grid_line, grid_column, "0", 0);
            fill_case(grid, grid_line, grid_column, text, MLV_COLOR_RED);
            return 1;
        }
    }
    else
    {
        /* removes the question mark if user clicks outside the value selector grid and puts back the old value */
        fill_case(grid, grid_line, grid_column, "0", 0);
        char text[2];
        sprintf(text, "%d", (*current_board)[grid_line][grid_column]);
        fill_case(grid, grid_line, grid_column, text, 0);

        return 0;
    }
}

int *find_already_used_values(Board current_board, int grid_line, int grid_column, int grid_size)
{
    int *nombres = malloc(sizeof(int) * 9);

    /* getting the values already used in the line and the column */
    int k;
    for (k = 0; k < grid_size; k++)
    {
        nombres[current_board[grid_line][k]] = 1;
        nombres[current_board[k][grid_column]] = 1;
    }

    /* find the start of the 3x3 square */
    int line_start = 3 * (grid_line / 3);
    int column_start = 3 * (grid_column / 3);
    int line_iterator, column_iterator;
    for (line_iterator = 0; line_iterator < 3; line_iterator++)
    {
        for (column_iterator = 0; column_iterator < 3; column_iterator++)
        {
            if ((line_start + line_iterator) == grid_line && (column_start + column_iterator) == grid_column)
            {
                continue;
            }
            else
            {
                nombres[current_board[line_start + line_iterator][column_start + column_iterator]] = 1;
            }
        }
    }
    return nombres;
}

int is_board_full(Board board, int grid_size)
{
    int line_iterator, column_iterator;
    for (line_iterator = 0; line_iterator < grid_size; line_iterator++)
    {
        for (column_iterator = 0; column_iterator < grid_size; column_iterator++)
        {
            if (board[line_iterator][column_iterator] == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}
