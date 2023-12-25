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
#include "types.h"
#include "util.h"
#include "individual.h"

void getIndividualStats(FILE *input, FILE *output)
{
    char buffer[MAX_MOVES];
    bool isWhitePlayer = false;
    bool isBlackPlayer = false;
    char whitePlayerName[MAX_PLAYER_NAME_LENGTH] = "";
    char blackPlayerName[MAX_PLAYER_NAME_LENGTH] = "";
    Players players;

    unsigned totalPlayers = getPlayers(input, players.playerNames);
    initializePlayers(&players, totalPlayers);

    for (int i = 0; i < totalPlayers; i++)
    {
        while (fgets(buffer, sizeof(buffer), input))
        {
            if (strstr(buffer, "[White "))
                (sscanf(buffer, "[White \"%[^\"]\"]", whitePlayerName));
            if (strstr(buffer, "[Black "))
                (sscanf(buffer, "[Black \"%[^\"]\"]", blackPlayerName));

            if (strcmp(whitePlayerName, players.playerNames[i]) == 0)
                isWhitePlayer = true;
            else
                isWhitePlayer = false;

            if (strcmp(blackPlayerName, players.playerNames[i]) == 0)
                isBlackPlayer = true;
            else
                isBlackPlayer = false;

            if (strstr(buffer, "1-0"))
            {
                if (isWhitePlayer)
                    players.individualWhiteWins[i]++;
                else if (isBlackPlayer)
                    players.individualBlackLosses[i]++;
            }
            else if (strstr(buffer, "0-1"))
            {
                if (isBlackPlayer)
                    players.individualBlackWins[i]++;
                else if (isWhitePlayer)
                    players.individualWhiteLosses[i]++;
            }
            else if (strstr(buffer, "1/2-1/2") && (isWhitePlayer || isBlackPlayer))
            {
                players.individualDraws[i]++;
            }

            if ((strstr(buffer, "1-0") || strstr(buffer, "0-1") || strstr(buffer, "1/2-1/2")) &&
                (isWhitePlayer || isBlackPlayer))
            {
                players.totalPlayerGames[i]++;
            }
        }
        rewind(input);
    }

    rewind(input);
    getIndividualAverageDepth(input, &players);
    getIndividualTotalMoveCount(input, &players);
    printIndividualStats(players, output, numGames(input), totalMoveCount(input));
}

void getIndividualAverageDepth(FILE *input, Players *players)
{
    char buffer[MAX_MOVES];
    bool isWhitePlayer = false;
    bool isBlackPlayer = false;
    bool isWhiteTurn = true;
    char whitePlayerName[MAX_PLAYER_NAME_LENGTH] = "";
    char blackPlayerName[MAX_PLAYER_NAME_LENGTH] = "";
    unsigned currentDepth = 0;
    unsigned individualTotalDepth[players->totalPlayers];
    unsigned move_count;

    for (int i = 0; i < players->totalPlayers; i++)
    {
        move_count = 0;
        individualTotalDepth[i] = 0;

        while (fgets(buffer, sizeof(buffer), input))
        {

            if (strstr(buffer, "[White "))
            {
                (sscanf(buffer, "[White \"%[^\"]\"]", whitePlayerName));
                isWhiteTurn = true;
            }
            if (strstr(buffer, "[Black "))
                (sscanf(buffer, "[Black \"%[^\"]\"]", blackPlayerName));

            if (strcmp(whitePlayerName, players->playerNames[i]) == 0)
                isWhitePlayer = true;
            else
                isWhitePlayer = false;

            if (strcmp(blackPlayerName, players->playerNames[i]) == 0)
                isBlackPlayer = true;
            else
                isBlackPlayer = false;

            char *movestart = FIND_MOVESTART(buffer);
            char *bookMove = BOOKMOVE(buffer);

            while (movestart)
            {
                if (!bookMove)
                {
                    if ((isWhitePlayer && isWhiteTurn) || (isBlackPlayer && !isWhiteTurn))
                    {
                        move_count++;
                        sscanf(movestart, "{%*[^/]/%u", &currentDepth);
                        individualTotalDepth[i] += currentDepth;
                    }
                }

                isWhiteTurn = !isWhiteTurn;
                movestart = strstr(movestart + 1, "{");
                bookMove = bookMove ? strstr(bookMove + 1, "{book}") : NULL;
            }
        }

        players->individualAverageDepth[i] = individualTotalDepth[i] / move_count;
        rewind(input);
    }
}

void getIndividualTotalMoveCount(FILE *input, Players *players)
{
    char buffer[MAX_MOVES];
    char whitePlayerName[MAX_PLAYER_NAME_LENGTH] = "";
    char blackPlayerName[MAX_PLAYER_NAME_LENGTH] = "";
    bool isWhitePlayer = false;
    bool isBlackPlayer = false;
    bool isWhiteTurn = true;

    for (int i = 0; i < players->totalPlayers; i++)
    {
        while (fgets(buffer, sizeof(buffer), input))
        {
            if (strstr(buffer, "[White "))
            {
                (sscanf(buffer, "[White \"%[^\"]\"]", whitePlayerName));
                isWhiteTurn = true;
            }
            if (strstr(buffer, "[Black "))
                (sscanf(buffer, "[Black \"%[^\"]\"]", blackPlayerName));

            if (strcmp(whitePlayerName, players->playerNames[i]) == 0)
                isWhitePlayer = true;
            else
                isWhitePlayer = false;

            if (strcmp(blackPlayerName, players->playerNames[i]) == 0)
                isBlackPlayer = true;
            else
                isBlackPlayer = false;

            char *movestart = FIND_MOVESTART(buffer);

            while (movestart)
            {
                if ((isWhitePlayer && isWhiteTurn) || (isBlackPlayer && !isWhiteTurn))
                    players->totalPlayerMoves[i]++;

                isWhiteTurn = !isWhiteTurn;
                movestart = strstr(movestart + 1, "{");
            }
        }
        rewind(input);
    }
}

void printIndividualStats(Players players, FILE *output, size_t totalGames, size_t totalMoves)
{
    fprintf(output, "Individual statistics for each player\n");
    fprintf(output, "=====================================\n");
    fprintf(output, "\nThere are exactly %u players in the PGN file:\n\n", players.totalPlayers);

    for (int i = 0; i < players.totalPlayers; i++)
    {
        fprintf(output, "- Player: %-20s\n", players.playerNames[i]);
        fprintf(output, "\t·White wins     : %-7u (%.2f%%)\n", players.individualWhiteWins[i],
                calculateWhiteWinPercentage(players.individualWhiteWins[i], players.totalPlayerGames[i]));
        fprintf(output, "\t·Black wins     : %-7u (%.2f%%)\n", players.individualBlackWins[i],
                calculateBlackWinPercentage(players.individualBlackWins[i], players.totalPlayerGames[i]));
        fprintf(output, "\t·Draws          : %-7u (%.2f%%)\n", players.individualDraws[i],
                calculateDrawPercentage(players.individualDraws[i], players.totalPlayerGames[i]));
        fprintf(output, "\t·Lost with white: %-7u (%.2f%%)\n", players.individualWhiteLosses[i],
                calculateBlackWinPercentage(players.individualWhiteLosses[i], players.totalPlayerGames[i]));
        fprintf(output, "\t·Lost with black: %-7u (%.2f%%)\n", players.individualBlackLosses[i],
                calculateWhiteWinPercentage(players.individualBlackLosses[i], players.totalPlayerGames[i]));
        fprintf(output, "\t·Total games    : %-7lu (%.2f%%)\n", players.totalPlayerGames[i],
                calculateGamePercentage(players.totalPlayerGames[i], totalGames));
        fprintf(output, "\t·Total moves    : %-7lu (%.2f%%)\n", players.totalPlayerMoves[i],
                calculateMovePercentage(players.totalPlayerMoves[i], totalMoves));
        fprintf(output, "\t·Win rate       : %.2f%%\n",
                calculateWinRate(players.individualWhiteWins[i], players.individualBlackWins[i],
                                 players.totalPlayerGames[i]));
        fprintf(output, "\t·Avg. Depth     : %-7u\n", players.individualAverageDepth[i]);

        if (i + 1 != players.totalPlayers)
            fprintf(output, "\n------------------------------\n\n");
        else
            fprintf(output, "\n==============================");
    }
}