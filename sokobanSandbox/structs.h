#pragma once
#include "structs.h"

typedef struct Save {
	int isNewState;
	int lastLevelPlayed;
} Save;

typedef struct Settings {
	int audio;
	unsigned int resolutionWidth;
	unsigned int resolutionHeight;
} Settings;

typedef struct Keybinds {
	char moveUp;
	char moveLeft;
	char moveDown;
	char moveRight;
	char undoMove;
	char resetMap;
} Keybinds;

typedef struct Config {
	Save save;
	Settings settings;
	Keybinds keybinds;
} Config;

typedef struct Customer {
	int posX;
	int posY;
	int direction;
	int range;
	int isCustomer;
	int isActive;
} Customer;

typedef struct Cell {
	int player;
	int key;
	int box;
	int boarder;
	Customer customer;
} Cell;

