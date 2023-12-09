#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"
#include "util.h"
#include "individual.h"

void getIndividualBasicStats(FILE *input, FILE *output)
{
    char playerNames[MAX_TOTAL_PLAYERS][MAX_PLAYER_NAME_LENGTH];
    char buffer[MAX_MOVES];
    bool currentPlayer = false;
    unsigned individualWhiteWins[MAX_TOTAL_PLAYERS] = {0};
    unsigned individualBlackWins[MAX_TOTAL_PLAYERS] = {0};
    unsigned individualDraws[MAX_TOTAL_PLAYERS] = {0};
    unsigned totalPlayerGames[MAX_TOTAL_PLAYERS] = {0};

    getPlayerNames(input, playerNames);

    for(int i = 0; i < MAX_TOTAL_PLAYERS; i++)
    {
        if(playerNames[i])
        {
            while(fgets(buffer, sizeof(buffer), input))
            {
                if(strstr(buffer, playerNames[i]))
                {
                    currentPlayer = true;
                }

                if(strstr(buffer, "1-0") && currentPlayer)
                {
                    individualWhiteWins[i]++;
                    totalPlayerGames[i]++;
                    currentPlayer = false;
                }
                else if(strstr(buffer, "0-1") && currentPlayer)
                {
                    individualBlackWins[i]++;
                    totalPlayerGames[i]++;
                    currentPlayer = false;
                }
                else if(strstr(buffer, "1/2-1/2") && currentPlayer)
                {
                    individualDraws[i]++;
                    totalPlayerGames[i]++;
                    currentPlayer = false;
                }
            }
            rewind(input);
        }
    }

    rewind(input);
    fprintf(output, "Individual statistics for each player:\n");
    fprintf(output, "--------------------------------------\n");

    for(int i = 0; i < MAX_TOTAL_PLAYERS; i++)
    {
        if(playerNames[i])
        {
            fprintf(output, "- Player: %s\n", playerNames[i]);
            fprintf(output, "- White wins: %u\n", individualWhiteWins[i]);
            fprintf(output, "- Black wins: %u\n", individualBlackWins[i]);
            fprintf(output, "- Draws: %u\n", individualDraws[i]);
            fprintf(output, "- Total games: %u\n", totalPlayerGames[i]);
            fprintf(output, "- Win rate: %.2f%%\n", calculateWinRate(individualWhiteWins[i], individualBlackWins[i]));
            fprintf(output, "\n");
        }
    }
}