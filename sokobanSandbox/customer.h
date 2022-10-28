#pragma once
#include "cprocessing.h"
#include "structs.h"
#include "defines.h"
#include "utils.h"

void customerLogic(int posX, int posY, int prevPosX, int prevPosY, int direction, Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]);
void customerMovement(int posX, int posY, Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS], int path[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]);
int customerLock(int posX, int posY, Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]);