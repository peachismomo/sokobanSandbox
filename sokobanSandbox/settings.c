#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "structs.h"
#include "defines.h"
#include "settings.h"

/*Reads config.ini*/
Config readFile() {
	/*Default settings if anything goes wrong. Will return this if anything goes wrong with reading.*/
	Config gameConfig = {
	.save.isNewState = 1,
	.save.lastLevelPlayed = 1,
	.settings.audio = 50,
	.settings.resolutionHeight = 1080,
	.settings.resolutionWidth = 1920,
	.keybinds.moveUp = 'W',
	.keybinds.moveLeft = 'A',
	.keybinds.moveDown = 'S',
	.keybinds.moveRight = 'D',
	.keybinds.undoMove = 'U',
	.keybinds.resetMap = 'R'
	};

	/*READ ONLY*/
	FILE* file;
	file = fopen("config.ini", "r");

	int section = 0;
	char line[TEXT_BUFFER] = { '\0' };

	if (file == NULL) {
		fprintf(stderr, "Error opening file.\n");
	}
	else {
		while (fgets(line, TEXT_BUFFER, file) != NULL) {
			/*'[' indicates a section name, therefore, check which section of config.ini the code is at.*/
			if (line[0] == '[') {
				char sectionName[TEXT_BUFFER];

				/*
				* Uses sscanf to read the section name.
				* [A-Za-z]: Only alphabetical characters are part of the scanset.
				* Should only scan 1 string.
				*/
				if (sscanf(line, "%[A-Za-z]s", &sectionName) == 1) {
					if (charArrayCompare(sectionName, "SAVESTATE")) {
						section = 1;
					}
					else if (charArrayCompare(sectionName, "SETTINGS")) {
						section = 2;
					}
					else if (charArrayCompare(sectionName, "KEYBINDS")) {
						section = 3;
					}
				}
			}

			/*(line[0] != '\n') ignores any empty lines*/
			else if (line[0] != '\n') {

				char settingName[TEXT_BUFFER];

				/*
				* Uses sscanf on each line to get key and value.
				* Format is "key = value" (%s = %d/c). value can be int or char.
				*/
				switch (section) {

					/*SAVESTATE*/
				case 1: {
					int value;
					if (sscanf(line, "%s = %d", settingName, &value) == 2) {
						if (charArrayCompare(settingName, "isNewState")) {
							gameConfig.save.isNewState = value;
						}
						else if (charArrayCompare(settingName, "lastLevelPlayed")) {
							gameConfig.save.lastLevelPlayed = value;
						}
					}
					break;
				}

					  /*SETTINGS*/
				case 2: {
					int value;
					if (sscanf(line, "%s = %d ", settingName, &value) == 2) {
						if (charArrayCompare(settingName, "audio")) {
							gameConfig.settings.audio = value;
						}
						else if (charArrayCompare(settingName, "resolutionWidth")) {
							gameConfig.settings.resolutionWidth = value;
						}
						else if (charArrayCompare(settingName, "resolutionHeight")) {
							gameConfig.settings.resolutionHeight = value;
						}
					}
					break;
				}

					  /*KEYBINDS*/
				case 3: {
					char keyBind;
					if (sscanf(line, "%s = %c ", settingName, &keyBind) == 2) {
						if (charArrayCompare(settingName, "moveUp")) {
							gameConfig.keybinds.moveUp = keyBind;
						}
						else if (charArrayCompare(settingName, "moveLeft")) {
							gameConfig.keybinds.moveLeft = keyBind;
						}
						else if (charArrayCompare(settingName, "moveDown")) {
							gameConfig.keybinds.moveDown = keyBind;
						}
						else if (charArrayCompare(settingName, "moveRight")) {
							gameConfig.keybinds.moveRight = keyBind;
						}
						else if (charArrayCompare(settingName, "undoMove")) {
							gameConfig.keybinds.undoMove = keyBind;
						}
						else if (charArrayCompare(settingName, "resetMap")) {
							gameConfig.keybinds.resetMap = keyBind;
						}
					}
					break;
				}

					  /*sscanf did not recognise any sections.*/
				default:
					fprintf(stderr, "Unrecognised section format while reading config.\n");
					break;
				}
			}
			/*Completely wrong file format.*/
			else {
				fprintf(stderr, "Unrecognised file format while reading config.\n");
			}
		}
	}

	/*Closes stream*/
	if (file != NULL) {
		fclose(file);
	}

	return gameConfig;
}

/*Checks if 2 char array (strings) are the same regardless of array size.*/
int charArrayCompare(char arr1[TEXT_BUFFER], const char* arr2) {
	int i = 0, sameString, isLoopBroken = 0;

	while (arr1[i] != '\0') {
		/*if any characters do not match, break the loop.*/
		if (arr1[i] != arr2[i]) {
			isLoopBroken = 1;
			break;
		}

		i++;
	}

	sameString = isLoopBroken ? 0 : (arr2[i] != '\0' ? 0 : 1);

	return sameString;
}

void createConfig(Config config) {
	FILE* file;
	file = fopen("config.ini", "w");

	/*If this fails, just run the game with default config.*/
	if (file == NULL) {

	}
	else {

	}
}

void updateConfig(Config config) {

}