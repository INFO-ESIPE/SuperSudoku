#ifndef _GRIDGENERATOR_
#define _GRIDGENERATOR_
#include "constants.h"
#include "grid_utility.h"

struct SuperSudoku generateMainGrid();
struct SuperSudoku generateMainGridFromFile(char* filePath);
void generateSubGrid(struct SuperSudoku grids, int subGridX, int subGridY);
void freeGrids(struct SuperSudoku grids);

#endif