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
    size_t totalPlayerGames[MAX_TOTAL_PLAYERS] = {0};

    unsigned totalPlayers = getPlayers(input, playerNames);

    for(int i = 0; i < totalPlayers; i++)
    {
        while(fgets(buffer, sizeof(buffer), input))
        {
            if(strstr(buffer, playerNames[i]))
                currentPlayer = true;
            
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

    rewind(input);
    size_t totalGames = numGames(input);

    fprintf(output, "Individual statistics for each player\n");
    fprintf(output, "=====================================\n");
    fprintf(output, "\nThere are exactly %u players in the PGN file:\n\n", totalPlayers);
    
    for (int i = 0; i < totalPlayers; i++)
    {
        fprintf(output, "- Player: %-20s\n", playerNames[i]);
        fprintf(output, "\t·White wins : %-5u (%.2f%%)\n", individualWhiteWins[i], calculateWhiteWinPercentage(individualWhiteWins[i], totalPlayerGames[i]));
        fprintf(output, "\t·Black wins : %-5u (%.2f%%)\n", individualBlackWins[i], calculateBlackWinPercentage(individualBlackWins[i], totalPlayerGames[i]));
        fprintf(output, "\t·Draws      : %-5u (%.2f%%)\n", individualDraws[i], calculateDrawPercentage(individualDraws[i], totalPlayerGames[i]));
        fprintf(output, "\t·Total games: %-5lu (%.2f%%)\n", totalPlayerGames[i], calculateGamePercentage(totalPlayerGames[i], totalGames));
        fprintf(output, "\t·Win rate   : %.2f%%\n", calculateWinRate(individualWhiteWins[i], individualBlackWins[i], totalPlayerGames[i]));
    
        if (i + 1 != totalPlayers)
            fprintf(output, "\n------------------------------\n\n");
        else
            fprintf(output, "\n==============================");
    }
}