#include "cprocessing.h"
#include "structs.h"
#include "customer.h"
#include "level.h"
#include "movement.h"
#include "utils.h"
#include "defines.h"
#include "settings.h"

Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS];
float cellSize, cellAlign, elapsedLock;
int totalObjs;
Config config;

void game_init(void) {
	/*Create empty grid*/
	for (int row = 0; row < SOKOBAN_GRID_ROWS; row++) {
		for (int col = 0; col < SOKOBAN_GRID_COLS; col++) {
			grid[row][col].boarder = 0;
			grid[row][col].key = 0;
			grid[row][col].player = 0;
			grid[row][col].box = 0;
			grid[row][col].customer.isCustomer = 0;
		}
	}

	/*Set grid characteristics here*/
	for (int row = 0; row < SOKOBAN_GRID_ROWS; row++) {
		grid[row][0].boarder = 1;
		//grid[row][3].boarder = 1;
		//grid[row][7].boarder = 1;
		//grid[row][8].boarder = 1;
		grid[row][SOKOBAN_GRID_COLS - 1].boarder = 1;
	}

	for (int col = 0; col < SOKOBAN_GRID_COLS; col++) {
		grid[0][col].boarder = 1;
		//grid[1][col].boarder = 1;
		//grid[2][col].boarder = 1;
		//grid[3][col].boarder = 1;
		//grid[4][col].boarder = 1;
		grid[SOKOBAN_GRID_ROWS - 1][col].boarder = 1;
	}

	grid[5][2].player = 1;

	grid[1][7].customer.posX = 1;
	grid[1][7].customer.posX = 7;
	grid[1][7].customer.direction = 2;
	grid[1][7].customer.range = 2;
	grid[1][7].customer.isCustomer = 1;
	grid[1][7].customer.isActive = 1;

	grid[6][3].box = 1;
	grid[8][1].key = 1;


	/*Settings*/
	// already declared in splash_screen. used for main.c -> basegame.c
	CP_System_SetWindowSize(CP_System_GetDisplayWidth() >> 1, CP_System_GetDisplayHeight() >> 1);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_StrokeWeight(0.5f);

	/*Config*/
	config = readFile();

	/*Initializations*/
	totalObjs = 2;
	elapsedLock = 0;
	cellSize = (float)CP_System_GetWindowHeight() * 1 / (float)SOKOBAN_GRID_ROWS;
	cellAlign = cellSize * 0.3f * SOKOBAN_GRID_ROWS; // 0.3f roughly aligns in the middle
}

void game_update(void) {
	/*Check for input and get the direction of the input*/
	int dir = getDirection();

	int playerPosX, playerPosY, cusX, cusY, isLocked = 0, isCompleted = 0;

	/*Read grid*/
	for (int row = 0; row < SOKOBAN_GRID_ROWS; row++) {
		for (int col = 0; col < SOKOBAN_GRID_COLS; col++) {
			/*Check if all objectives has been reached*/
			if (grid[col][row].key && grid[col][row].box)
				isCompleted++;

			/*Get position of player*/
			if (grid[row][col].player) {
				playerPosX = row;
				playerPosY = col;
			}

			if (customerLock(row, col, grid)) {
				isLocked = 1;
				cusX = row;
				cusY = col;
			}

		}
	}

	/*If all objectives reached, do something here*/
	if (isCompleted == totalObjs) {
		//CP_Engine_Terminate();
	}

	/*If player is stunlocked by customer*/
	if (isLocked) {
		/*Check if 3 seconds has passed*/
		if (elapsedLock < 3) {
			elapsedLock += CP_System_GetDt();
		}
		else {
			/*Reset timer and turn customer inactive*/
			elapsedLock = 0;
			isLocked = 0;
			grid[cusX][cusY].customer.isActive = 0;
		}
	}

	else {
		/*Game logic*/
		if (dir > 0) {
			getCell(playerPosX, playerPosY, dir, grid);
		}
	}


	/*Rendering grid*/
	CP_Graphics_ClearBackground(WHITE);

	for (int row = 0; row < SOKOBAN_GRID_ROWS; row++) {
		for (int col = 0; col < SOKOBAN_GRID_COLS; col++) {
			Cell currCell = grid[row][col];

			float cellX = cellSize * col + cellAlign;
			float cellY = cellSize * row;

			if (currCell.boarder || currCell.box || currCell.key || currCell.player || currCell.customer.isCustomer) {
				if (currCell.boarder)
					CP_Settings_Fill(BLACK);

				else if (currCell.player)
					CP_Settings_Fill(RED);

				else if (currCell.key && currCell.box)
					CP_Settings_Fill(VIOLET);

				else if (currCell.box)
					CP_Settings_Fill(BLUEGRAY);

				else if (currCell.key)
					CP_Settings_Fill(YELLOW);

				else if (currCell.customer.isCustomer)
					CP_Settings_Fill(BROWN);

				CP_Graphics_DrawRect(cellX, cellY, cellSize, cellSize);
			}
		}
	}
}

void game_exit(void) {

}
