#include "cprocessing.h"
#include "structs.h"
#include "defines.h"
#include "utils.h"

/*
* getDirection - returns the direction by input.
*/
int getDirection(void) {
	if (CP_Input_KeyTriggered(KEY_W))
		return SOKOBAN_UP;

	else if (CP_Input_KeyTriggered(KEY_A))
		return SOKOBAN_LEFT;

	else if (CP_Input_KeyTriggered(KEY_S))
		return SOKOBAN_DOWN;

	else if (CP_Input_KeyTriggered(KEY_D))
		return SOKOBAN_RIGHT;

	return SOKOBAN_IDLE;
}

/*
* gameLogic - Logic and interactions between players, boxes, objective and boarders.
* int posX, posY: The next cell that the player is moving towards.
* int nextPosX, nextPosY: The following cell after the next cell.
* int prevPosX, prevPosY: The previous cell that the player was previously at.
*/
void gameLogic(int posX, int posY, int nextPosX, int nextPosY, int prevPosX, int prevPosY, Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]) {
	/*Push box (No boarder or another box blocking the box being pushed)*/
	if (grid[posX][posY].box && !grid[nextPosX][nextPosY].box && !grid[nextPosX][nextPosY].customer.isCustomer && !grid[posX][posY].boarder && !grid[nextPosX][nextPosY].boarder && !grid[nextPosX][nextPosY].customer.isCustomer)
	{
		grid[prevPosX][prevPosY].player = 0;
		grid[posX][posY].player = 1;
		grid[posX][posY].box = 0;
		grid[nextPosX][nextPosY].box = 1;
	}

	/*Player movement without obstruction*/
	else if (!grid[posX][posY].box && !grid[posX][posY].boarder && !grid[posX][posY].customer.isCustomer) {
		grid[prevPosX][prevPosY].player = 0;
		grid[posX][posY].player = 1;
	}
}

void getCell(int posX, int posY, int direction, Cell grid[SOKOBAN_GRID_ROWS][SOKOBAN_GRID_COLS]) {
	switch (direction) {
		/* Move up */
	case SOKOBAN_UP:
		--posX;
		gameLogic(posX, posY, posX - 1, posY, posX + 1, posY, grid);
		break;

		/* Move left */
	case SOKOBAN_LEFT:
		--posY;
		gameLogic(posX, posY, posX, posY - 1, posX, posY + 1, grid);
		break;

		/* Move down */
	case SOKOBAN_DOWN:
		++posX;
		gameLogic(posX, posY, posX + 1, posY, posX - 1, posY, grid);
		break;

		/* Move right */
	case SOKOBAN_RIGHT:
		++posY;
		gameLogic(posX, posY, posX, posY + 1, posX, posY - 1, grid);
		break;

		/* Default case (if any) */
	default:
		break;
	}
}
