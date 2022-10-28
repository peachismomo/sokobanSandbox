#pragma once
#include "cprocessing.h"
#include "structs.h"
#include "defines.h"

void setMap(Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]);
int getObjective(Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]);
int moveCount(int move, Cell moves[MOVE][SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS], Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]);
int undoMove(int move, Cell moves[MOVE][SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS], Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]);
int resetMap(int move, Cell moves[MOVE][SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS], Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]);
