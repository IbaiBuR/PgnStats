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

#pragma once

#define NUM_ECOS 5
#define MAX_MOVES 4096
#define MAX_RESULT_LINE 8
#define MAX_GAME_START_LINE 15
#define MAX_GAME_END_LINE 12
#define MAX_PLAYER_NAME_LENGTH 250
#define MAX_TOTAL_PLAYERS 100
#define TEMPORAL_PGN "temporal.pgn"
#define OVERALL_STATS_FILE_NAME "overall_statistics.txt"
#define INDIVIDUAL_STATS_FILE_NAME "individual_statistics.txt"

#define FIND_MOVESTART(buffer) strstr(buffer, "{")
#define BOOKMOVE(buffer) strstr(buffer, "{book}")

typedef struct Players
{
    char playerNames[MAX_TOTAL_PLAYERS][MAX_PLAYER_NAME_LENGTH];
    size_t totalPlayerGames[MAX_TOTAL_PLAYERS];
    size_t totalPlayerMoves[MAX_TOTAL_PLAYERS];
    unsigned individualWhiteWins[MAX_TOTAL_PLAYERS];
    unsigned individualBlackWins[MAX_TOTAL_PLAYERS];
    unsigned individualDraws[MAX_TOTAL_PLAYERS];
    unsigned individualWhiteLosses[MAX_TOTAL_PLAYERS];
    unsigned individualBlackLosses[MAX_TOTAL_PLAYERS];
    unsigned individualAverageDepth[MAX_TOTAL_PLAYERS];
    unsigned totalPlayers;
} Players;

typedef struct Statistics
{
    size_t noBookMoveCount;
    size_t totalMoveCount;
    size_t numGames;
    unsigned draws;
    unsigned white_wins;
    unsigned black_wins;
    unsigned averagePlyCount;
    unsigned averageDepth;
    unsigned ecoCodeGames[NUM_ECOS];
    double averageGameDuration;
    double averageTimePerMove;
    double averageEcoCodes[NUM_ECOS];
} Statistics;
