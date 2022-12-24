#ifndef _MOUSELISTENER_
#define _MOUSELISTENER_

#include "grid_frame.h"
#include "grid_utility.h"

/*Bibliothèque graphique*/
#include <MLV/MLV_all.h>

struct SelectorSlotLocation {
  int x;
  int y; 
};

void* mouseClick(void* args);
void mouseOver(void *args);
void startListenMouse(struct SuperSudoku grids);
void freeListener();

void emptyCurrentSelectedSlot();
int slotIsEmpty(struct SlotLocation slotLocation);
struct SlotLocation getCurrentSelectedSlot();

int getCurrentOverSelectorSlot();
int getCurrentOverSlotLocation(struct SlotLocation *overSlotLocation);
#endif
