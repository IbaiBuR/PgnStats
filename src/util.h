#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdbool.h>
#include "types.h"

void deleteTags(FILE *, FILE *); // removes conflicting tags from the input pgn file
void getOutputFileName(char *, char *); // gets the output txt file name based on the input pgn file name
bool tagIsPresent(FILE *, char *); //returns true if the specified tagName is found in the PGN file, otherwise it returns false
bool isFound(char *, char [MAX_TOTAL_PLAYERS][MAX_PLAYER_NAME_LENGTH]); // returns true if the playerName is found in the playerNames array

#endif