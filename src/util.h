#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdbool.h>
#include "types.h"

void deleteTags(FILE *, FILE *); // removes conflicting tags from the input PGN file
void initializePlayers(Players *, unsigned); // initializes the Players struct
void initializeStatistics(Statistics *); // initializes the Statistics struct
bool tagIsPresent(FILE *, char *); //returns true if the specified tagName is found in the PGN file, otherwise it returns false
bool isFound(char *, char [MAX_TOTAL_PLAYERS][MAX_PLAYER_NAME_LENGTH]); // returns true if the playerName is found in the playerNames array
double calculateWhiteWinPercentage(unsigned, size_t); // returns the white win percentage
double calculateBlackWinPercentage(unsigned, size_t); // returns the black win percentage
double calculateDrawPercentage(unsigned, size_t); // returns the draw percentage
double calculateWinRate(unsigned, unsigned, size_t); // returns the win rate
double calculateGamePercentage(size_t, size_t); // returns the game percentage
double calculateMovePercentage(size_t, size_t);
unsigned getPlayers(FILE *, char [MAX_TOTAL_PLAYERS][MAX_PLAYER_NAME_LENGTH]); // returns the number of players in the PGN file
size_t numGames(FILE *); //returns the total number of games in the PGN file
size_t noBookMoveCount(FILE *); // returns the total number of non-book moves in the PGN file
size_t totalMoveCount(FILE *); // return the total number of moves in the PGN file

#endif