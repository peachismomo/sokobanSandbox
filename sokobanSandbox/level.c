#define _CRT_SECURE_NO_WARNINGS //Added to use fopen & fscanf instead of fopen_s & fscanf_s
#include "cprocessing.h"
#include "structs.h"
#include "defines.h"
#include "utils.h"
#include <stdio.h> //Added for parsing CSV file
#include <errno.h> //Added for error handling/checking of parsing CSV file

/*Parse CSV file to initialise grid array at the start of every stage/level*/
void setMap(Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]) {
	printf("In setMap! \n");
	int boarder = 0, key = 0, player = 0, box = 0, row = 0, col = 0, read = 0, records = 0;
	FILE* csvFile;
	char file[] = "..\\..\\Extern\\level_mapper\\test_level.csv";
	csvFile = 0;
	csvFile = fopen(file, "r");

	if (NULL == csvFile) {
		printf("%s \n", &file);
		printf("Error : errno='%s'.\n", strerror(errno));
		printf("File Opening Failed!\n");
		exit(1);
	}
	do {
		if (col == SOKOBAN_GRID_COLS) {
			row++;
			col = 0;
		}
		read = fscanf(csvFile, "%d,%d,%d,%d\n", &grid[row][col].boarder, &grid[row][col].key, &grid[row][col].player, &grid[row][col].box);
		printf("row is %d, col is %d, boarder is %d \n", row, col, grid[row][col].boarder);
		if (read == 4) col++;

		if (read != 4 && !feof(csvFile)) {
			printf("File format incorrect. \n");
		}
		if (ferror(csvFile)) {
			printf("Error reading file.\n");
		}
	} while (!feof(csvFile));

	fclose(csvFile);
}

/*Counts the number of key objective points in the grid and returns it*/
int getObjective(Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]) {
	int objective = 0;
	for (int row = 0; row < SOKOBAN_GRID_ROWS; row++) {
		for (int col = 0; col < SOKOBAN_GRID_COLS; col++) {
			if (grid[row][col].key) objective++;
		}
	}
	return objective;
}

/*Counts the number of moves and saves the previous state of the grid to a new array 'moves'*/
int moveCount(int move, Cell moves[MOVE][SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS], Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]) {
	for (int row = 0; row < SOKOBAN_GRID_ROWS; row++) {
		for (int col = 0; col < SOKOBAN_GRID_COLS; col++) {
			moves[move][row][col] = grid[row][col];
		}
	}
	printf("Current Moves: %d\n", ++move);
	return move;
}

/*Sets current 'grid' array to the previous 'moves' array to undo a move, decrement number of moves*/
int undoMove(int move, Cell moves[MOVE][SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS], Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]) {
	if (move > 0) {
		for (int row = 0; row < SOKOBAN_GRID_ROWS; row++) {
			for (int col = 0; col < SOKOBAN_GRID_COLS; col++) {
				grid[row][col] = moves[move - 1][row][col];
				moves[move - 1][row][col].boarder = 0;
				moves[move - 1][row][col].key = 0;
				moves[move - 1][row][col].player = 0;
				moves[move - 1][row][col].box = 0;
			}
		}
		printf("Current Moves: %d\n", --move);
	}
	return move;
}

/*Resets grid to the initial state based on the CSV, resets move to 0*/
int resetMap(int move, Cell moves[MOVE][SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS], Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]) {
	for (int map = 0; map < move; map++) {
		for (int row = 0; row < SOKOBAN_GRID_ROWS; row++) {
			for (int col = 0; col < SOKOBAN_GRID_COLS; col++) {
				moves[move][row][col].boarder = 0;
				moves[move][row][col].key = 0;
				moves[move][row][col].player = 0;
				moves[move][row][col].box = 0;
			}
		}
	}
	setMap(grid);
	return move = 0;
}