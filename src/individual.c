#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"
#include "util.h"
#include "individual.h"

void getIndividualStats(FILE *input, FILE *output)
{
    char buffer[MAX_MOVES];
    bool currentPlayer = false;
    Players players;

    unsigned totalPlayers = getPlayers(input, players.playerNames);
    initializePlayers(&players, totalPlayers);

    for(int i = 0; i < totalPlayers; i++)
    {
        while(fgets(buffer, sizeof(buffer), input))
        {
            if(strstr(buffer, players.playerNames[i]))
                currentPlayer = true;
            
            if(strstr(buffer, "1-0") && currentPlayer)
            {
                players.individualWhiteWins[i]++;
                players.totalPlayerGames[i]++;
                currentPlayer = false;
            }
            else if(strstr(buffer, "0-1") && currentPlayer)
            {
                players.individualBlackWins[i]++;
                players.totalPlayerGames[i]++;
                currentPlayer = false;
            }
            else if(strstr(buffer, "1/2-1/2") && currentPlayer)
            {
                players.individualDraws[i]++;
                players.totalPlayerGames[i]++;
                currentPlayer = false;
            }
        }
        rewind(input);
    }

    rewind(input);
    getIndividualAverageDepth(input, &players);
    printIndividualStats(players, output, numGames(input));
}

unsigned * getIndividualAverageDepth(FILE *input, Players *players)
{
    char buffer[MAX_MOVES];
    bool currentPlayer = false;
    unsigned currentDepth = 0;
    unsigned individualTotalDepth[players->totalPlayers];
    unsigned move_count;

    for(int i = 0; i < players->totalPlayers; i++)
    {
        move_count = 0;
        while(fgets(buffer, sizeof(buffer), input))
        {
            if(strstr(buffer, players->playerNames[i]))
                currentPlayer = true;
            
            char *movestart = FIND_MOVESTART(buffer);

            if(movestart && currentPlayer && !(strstr(buffer, "{book}")))
            {
                sscanf(movestart, "{%*f/%u %*f%*c}", &currentDepth);
                individualTotalDepth[i] += currentDepth;
                move_count++;
            }
        }
        players->individualAverageDepth[i] = individualTotalDepth[i] / move_count;
        rewind(input);
    }

    return players->individualAverageDepth;
}

void printIndividualStats(Players players, FILE *output, size_t totalGames)
{
    fprintf(output, "Individual statistics for each player\n");
    fprintf(output, "=====================================\n");
    fprintf(output, "\nThere are exactly %u players in the PGN file:\n\n", players.totalPlayers);
    
    for (int i = 0; i < players.totalPlayers; i++)
    {
        fprintf(output, "- Player: %-20s\n", players.playerNames[i]);
        fprintf(output, "\t·White wins : %-5u (%.2f%%)\n", players.individualWhiteWins[i], calculateWhiteWinPercentage(players.individualWhiteWins[i], players.totalPlayerGames[i]));
        fprintf(output, "\t·Black wins : %-5u (%.2f%%)\n", players.individualBlackWins[i], calculateBlackWinPercentage(players.individualBlackWins[i], players.totalPlayerGames[i]));
        fprintf(output, "\t·Draws      : %-5u (%.2f%%)\n", players.individualDraws[i], calculateDrawPercentage(players.individualDraws[i], players.totalPlayerGames[i]));
        fprintf(output, "\t·Total games: %-5lu (%.2f%%)\n", players.totalPlayerGames[i], calculateGamePercentage(players.totalPlayerGames[i], totalGames));
        fprintf(output, "\t·Win rate   : %.2f%%\n", calculateWinRate(players.individualWhiteWins[i], players.individualBlackWins[i], players.totalPlayerGames[i]));
        fprintf(output, "\t·Avg. Depth : %-5u\n", players.individualAverageDepth[i]);
    
        if (i + 1 != players.totalPlayers)
            fprintf(output, "\n------------------------------\n\n");
        else
            fprintf(output, "\n==============================");
    }
}