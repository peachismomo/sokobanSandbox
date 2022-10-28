#include "cprocessing.h"
#include "math.h"
#include "structs.h"
#include "defines.h"
#include "utils.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	// finding X1,Y1 coords -- top left corner of the rectangle
	float x1 = area_center_x - area_width * 0.5f;
	float y1 = area_center_y - area_height * 0.5f;
	// finding X2,Y2 coords -- bottom right corner of the rectangle
	float x2 = area_center_x + area_width * 0.5f;
	float y2 = area_center_y + area_height * 0.5f;
	return ((click_x<x2&& click_x>x1 && click_y<y2&& click_y>y1) ? 1 : 0); // return 1 if the mouse is within the rectangle
}

/*
* timer - timer takes in the duration given (seconds) and returns the duration left.
* duration - Seconds given to complete the level
* startTime - Current time when loaded into the game state (declare startTime during the Init of level)
*/
int timer(int duration, float startTime) {
	int diffTime = (int)CP_System_GetSeconds() - (int)startTime;
	int remaindingTime = duration - diffTime;

	if (!(remaindingTime < 0)) {
		return remaindingTime;
	}
	else {
		return 0;
	}
}