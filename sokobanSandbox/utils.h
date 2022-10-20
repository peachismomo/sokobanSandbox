#pragma once
#include "structs.h"
#include "defines.h"

int getDirection(void);

void getCell(int posX, int posY, int direction, Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]);

void gameLogic(int posX, int posY, int nextPosX, int nextPosY, int prevPosX, int prevPosY, Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]);

int customerLock(int posX, int posY, Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]);