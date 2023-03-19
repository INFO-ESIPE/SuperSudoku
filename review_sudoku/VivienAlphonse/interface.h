#ifndef INTERFACE_H
#define INTERFACE_H

#include "main.h"

void prepare_grid_properties(struct Grid_properties *grid, int width, int height, char *title, int size_of_grid);
void init_interface(struct Grid_properties grid);
void init_grid(Board board, struct Grid_properties grid);
int pixel_coordinates_to_grid_coordinates(int x, int y, struct Grid_properties grid, int *grid_line, int *grid_column);
int grid_coordinates_to_pixel_coordinates(int grid_line, int grid_column, struct Grid_properties grid, int *x, int *y);
int show_value_selector_grid(struct Grid_properties grid, int *unavailable_values);
int are_coordinates_outside_the_grids(int x, int y, struct Grid_properties grid, int width_value_selector_grid, int margin_left_or_right, int margin_top, int cell_size_of_value_selector_grid);
int are_coordinates_inside_the_value_selector_grid(int x, int y, struct Grid_properties grid, int margin_left_or_right, int margin_top, int cell_size_of_value_selector_grid);
int fill_case(struct Grid_properties grid, int grid_line, int grid_column, char *text, int text_color);
void game_over(struct Grid_properties grid, int game_result);

#endif /* INTERFACE_H */