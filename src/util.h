/* PgnStats is a chess tool written in C
 Copyright (C) 2023 Ibai Burgos

 PgnStats is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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