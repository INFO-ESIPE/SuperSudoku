#ifndef _GRIDGENERATOR_
#define _GRIDGENERATOR_
#include "constants.h"
#include "grid_utility.h"


struct SuperSudoku generateMainGrid();
void generateSubGrid(struct SuperSudoku grids, int subGridX, int subGridY);
void consolePrintMainGrid(SudokuGrid grid);
void freeGrids(struct SuperSudoku grids);

#endif