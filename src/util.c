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

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"
#include "types.h"

void deleteTags(FILE *input, FILE *output)
{
    char line[MAX_MOVES];

    while (fgets(line, sizeof(line), input))
    {
        if (!(strncmp(line, "[Result ", MAX_RESULT_LINE) == 0 ||
              strncmp(line, "[GameStartTime ", MAX_GAME_START_LINE) == 0 ||
              strncmp(line, "[GameEndTime ", MAX_GAME_END_LINE) == 0))
            fputs(line, output);
    }

    rewind(input);
}

void initializePlayers(Players *players, unsigned totalPlayers)
{
    players->totalPlayers = totalPlayers;

    for (int i = 0; i < MAX_TOTAL_PLAYERS; i++)
    {
        players->individualWhiteWins[i] = 0;
        players->individualBlackWins[i] = 0;
        players->individualWhiteLosses[i] = 0;
        players->individualBlackLosses[i] = 0;
        players->individualDraws[i] = 0;
        players->totalPlayerGames[i] = 0;
        players->individualAverageDepth[i] = 0;
        players->totalPlayerMoves[i] = 0;
    }
}

void initializeStatistics(Statistics *statistics)
{
    statistics->noBookMoveCount = 0;
    statistics->totalMoveCount = 0;
    statistics->numGames = 0;
    statistics->draws = 0;
    statistics->white_wins = 0;
    statistics->black_wins = 0;
    statistics->averagePlyCount = 0;
    statistics->averageDepth = 0;
}

unsigned getPlayers(FILE *input, char playerNames[MAX_TOTAL_PLAYERS][MAX_PLAYER_NAME_LENGTH])
{
    char buffer[MAX_MOVES];
    char whitePlayerName[MAX_PLAYER_NAME_LENGTH] = "";
    char blackPlayerName[MAX_PLAYER_NAME_LENGTH] = "";
    unsigned totalPlayerCount = 0;

    while (fgets(buffer, sizeof(buffer), input))
    {
        if (strstr(buffer, "[White "))
            (sscanf(buffer, "[White \"%[^\"]\"]", whitePlayerName));
        if (strstr(buffer, "[Black "))
            (sscanf(buffer, "[Black \"%[^\"]\"]", blackPlayerName));

        if (whitePlayerName[0] && blackPlayerName[0])
        {
            if (totalPlayerCount < MAX_TOTAL_PLAYERS)
            {
                if (!isFound(whitePlayerName, playerNames))
                {
                    strncpy(playerNames[totalPlayerCount], whitePlayerName, MAX_PLAYER_NAME_LENGTH);
                    playerNames[totalPlayerCount][MAX_PLAYER_NAME_LENGTH - 1] = '\0';
                    totalPlayerCount++;
                }
                if (!isFound(blackPlayerName, playerNames))
                {
                    strncpy(playerNames[totalPlayerCount], blackPlayerName, MAX_PLAYER_NAME_LENGTH);
                    playerNames[totalPlayerCount][MAX_PLAYER_NAME_LENGTH - 1] = '\0';
                    totalPlayerCount++;
                }
            }
        }
    }

    rewind(input);
    return totalPlayerCount;
}

bool tagIsPresent(FILE *input, char *tagName)
{
    char buffer[MAX_MOVES];
    bool tagInFile = false;

    while (fgets(buffer, sizeof(buffer), input) && !tagInFile)
    {
        tagInFile = strstr(buffer, tagName);
    }

    rewind(input);

    return tagInFile;
}

bool isFound(char *playerName, char playerNames[MAX_TOTAL_PLAYERS][MAX_PLAYER_NAME_LENGTH])
{
    bool found = false;

    for (int i = 0; i < MAX_TOTAL_PLAYERS && !found; i++)
    {
        if (strcmp(playerName, playerNames[i]) == 0)
            found = true;
    }

    return found;
}

double calculateWhiteWinPercentage(unsigned whiteWins, size_t totalGames)
{
    return (double) whiteWins / totalGames * 100;
}

double calculateBlackWinPercentage(unsigned blackWins, size_t totalGames)
{
    return (double) blackWins / totalGames * 100;
}

double calculateDrawPercentage(unsigned draws, size_t totalGames)
{
    return (double) draws / totalGames * 100;
}

double calculateWinRate(unsigned whiteWins, unsigned blackWins, size_t totalGames)
{
    return (double) (whiteWins + blackWins) / totalGames * 100;
}

double calculateGamePercentage(size_t totalGames, size_t totalGamesInFile)
{
    return (double) totalGames / totalGamesInFile * 100;
}

double calculateMovePercentage(size_t totalMoves, size_t totalMovesInFile)
{
    return (double) totalMoves / totalMovesInFile * 100;
}

size_t numGames(FILE *input)
{
    char buffer[MAX_MOVES];
    size_t games = 0;

    while (fgets(buffer, sizeof(buffer), input))
    {
        if (strstr(buffer, "[White "))
            games++;
    }

    rewind(input);

    return games;
}

size_t noBookMoveCount(FILE *input)
{
    char buffer[MAX_MOVES];
    size_t moveCount = 0;

    while (fgets(buffer, sizeof(buffer), input))
    {
        char *movestart = FIND_MOVESTART(buffer);
        char *bookMove = BOOKMOVE(buffer);

        while (movestart)
        {
            if (!bookMove)
                moveCount++;

            movestart = strstr(movestart + 1, "{");
            bookMove = bookMove ? strstr(bookMove + 1, "{book}") : NULL;
        }
    }

    rewind(input);

    return moveCount;
}

size_t totalMoveCount(FILE *input)
{
    char buffer[MAX_MOVES];
    size_t moveCount = 0;

    while (fgets(buffer, sizeof(buffer), input))
    {
        char *movestart = FIND_MOVESTART(buffer);

        while (movestart)
        {
            moveCount++;
            movestart = strstr(movestart + 1, "{");
        }
    }

    rewind(input);

    return moveCount;
}