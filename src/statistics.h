#ifndef STATISTICS_H
#define STATISTICS_H

#include <stdio.h>
#include <stdbool.h>
#include "types.h"

void getStats(FILE *, FILE *); //gets some basic statistics of the input pgn file
void getAvgGD(FILE *, FILE *); //gets the average game duration of the input pgn file
void getAvgPC(FILE *, FILE *); //gets the average PlyCount of the input pgn file
void getAvgD(FILE *, FILE *); //gets the average depth per move of the input pgn file
void getAvgT(FILE *, FILE *); //gets the average time per move of the input pgn file
void getAvgEco(FILE *, FILE *); //gets the average eco code distribution of the input pgn file
void getPlayerNames(FILE *, char [MAX_TOTAL_PLAYERS][MAX_PLAYER_NAME_LENGTH]); // returns a char array containing the names of the players in the PGN file
size_t numGames(FILE *); //returns the total number of games in the PGN file

#endif