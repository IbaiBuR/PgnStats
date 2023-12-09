#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdbool.h>
#include "types.h"

void deleteTags(FILE *, FILE *); // removes conflicting tags from the input pgn file
void getOutputFileName(char *, char *); // gets the output txt file name based on the input pgn file name
void getPlayerNames(FILE *, char [MAX_TOTAL_PLAYERS][MAX_PLAYER_NAME_LENGTH]); // returns a char array containing the names of the players in the PGN file
bool tagIsPresent(FILE *, char *); //returns true if the specified tagName is found in the PGN file, otherwise it returns false
bool isFound(char *, char [MAX_TOTAL_PLAYERS][MAX_PLAYER_NAME_LENGTH]); // returns true if the playerName is found in the playerNames array
double calculateWhiteWinPercentage(unsigned, size_t); // returns the white win percentage
double calculateBlackWinPercentage(unsigned, size_t); // returns the black win percentage
double calculateDrawPercentage(unsigned, size_t); // returns the draw percentage
double calculateWinRate(unsigned, unsigned, size_t); // returns the win rate

#endif