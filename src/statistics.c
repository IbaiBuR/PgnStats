#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "statistics.h"
#include "util.h"

void getOverallStats(FILE *input, FILE *output)
{
    char line[MAX_MOVES];
    Statistics pgnStats;

    initializeStatistics(&pgnStats);

    while (fgets(line, sizeof(line), input))
    {
        if (strstr(line, "1/2-1/2"))
            pgnStats.draws++;
        else if (strstr(line, "1-0"))
            pgnStats.white_wins++;
        else if (strstr(line, "0-1"))
            pgnStats.black_wins++;
    }

    rewind(input);

    pgnStats.numGames = numGames(input);
    pgnStats.noBookMoveCount = noBookMoveCount(input);
    pgnStats.totalMoveCount = totalMoveCount(input);

    getAverageGameDuration(input, &pgnStats);
    getAveragePlyCount(input, &pgnStats);
    getAverageDepth(input, &pgnStats);
    getAverageTimePerMove(input, &pgnStats);
    getAverageEco(input, &pgnStats);

    printOverallStats(pgnStats, output);

}

void getAverageGameDuration(FILE *input, Statistics *statistics)
{
    char buffer[MAX_MOVES];
    double duration, totalDuration = 0;

    if (tagIsPresent(input, "[GameDuration "))
    {
        while (fgets(buffer, sizeof(buffer), input))
        {
            if (!(strncmp(buffer, "[GameDuration ", 14)))
            {
                char *duration_string = strtok(buffer, "\"");  // skip the tag
                duration_string = strtok(NULL, "\"");  // get the duration string

                // Parse the duration string to extract the hours, minutes, and seconds
                int hours = atoi(strtok(duration_string, ":"));
                int minutes = atoi(strtok(NULL, ":"));
                int seconds = atoi(strtok(NULL, ":"));

                // Convert the duration to seconds
                duration = hours * 3600 + minutes * 60 + seconds;
                totalDuration += duration;
            }
        }

        rewind(input);
        statistics->averageGameDuration = (double) totalDuration / statistics->numGames;
    }
}

void getAveragePlyCount(FILE *input, Statistics *statistics)
{
    char buffer[MAX_MOVES];
    unsigned totalPlyCount = 0, plyCount;

    if (tagIsPresent(input, "[PlyCount "))
    {
        while (fgets(buffer, sizeof(buffer), input))
        {
            if (strstr(buffer, "[PlyCount "))
            {
                sscanf(buffer, "[PlyCount \"%u\"]", &plyCount);
                totalPlyCount += plyCount;
            }
        }

        statistics->averagePlyCount = totalPlyCount / statistics->numGames;
        rewind(input);
    }

}

void getAverageDepth(FILE *input, Statistics *statistics)
{
    char buffer[MAX_MOVES];
    unsigned currentDepth;
    size_t totalDepth = 0;

    while (fgets(buffer, sizeof(buffer), input))
    {
        char *movestart = FIND_MOVESTART(buffer);
        char *bookMove = BOOKMOVE(buffer);

        while (movestart)
        {
            if (!bookMove)
            {
                sscanf(movestart, "{%*[^/]/%u", &currentDepth);
                totalDepth += currentDepth;
            }

            movestart = strstr(movestart + 1, "{");
            bookMove = bookMove ? strstr(bookMove + 1, "{book}") : NULL;
        }
    }

    rewind(input);

    statistics->averageDepth = totalDepth / statistics->noBookMoveCount;
}

void getAverageTimePerMove(FILE *input, Statistics *statistics)
{
    char buffer[MAX_MOVES];
    char *formatting = (char *) malloc(2 * sizeof(char));
    float time;
    double totalTime = 0;

    while (fgets(buffer, sizeof(buffer), input))
    {
        char *movestart = FIND_MOVESTART(buffer);
        char *bookMove = BOOKMOVE(buffer);

        while (movestart)
        {
            if (!bookMove)
            {
                sscanf(movestart, "{%*f/%*u %f%2s}", &time, formatting);

                if (strncmp(formatting, "ms", 2) == 0)
                    time /= 1000.0;

                totalTime += time;
            }

            movestart = strstr(movestart + 1, "{");
            bookMove = bookMove ? strstr(bookMove + 1, "{book}") : NULL;
        }
    }

    rewind(input);
    statistics->averageTimePerMove = (double) totalTime / statistics->noBookMoveCount;
}

void getAverageEco(FILE *input, Statistics *statistics)
{
    unsigned ECO_CODES[NUM_ECOS] = {0};
    char eco_letter;
    char buffer[MAX_MOVES];

    if (tagIsPresent(input, "[ECO "))
    {
        while (fgets(buffer, sizeof(buffer), input))
        {
            if (strstr(buffer, "[ECO "))
            {
                sscanf(buffer, "[ECO \"%c%*c%*c\"]", &eco_letter);
                ECO_CODES[eco_letter - 'A' + 0]++;
            }
        }

        rewind(input);

        for (int i = 0; i < 5; i++)
        {
            statistics->averageEcoCodes[i] = ((double) ECO_CODES[i] / statistics->numGames * 100);
            statistics->ecoCodeGames[i] = ECO_CODES[i];
        }
    }
}

void printOverallStats(Statistics statistics, FILE *output)
{
    double whiteWinPercentage = calculateWhiteWinPercentage(statistics.white_wins, statistics.numGames);
    double blackWinPercentage = calculateBlackWinPercentage(statistics.black_wins, statistics.numGames);
    double drawPercentage = calculateDrawPercentage(statistics.draws, statistics.numGames);
    double winRate = calculateWinRate(statistics.white_wins, statistics.black_wins, statistics.numGames);

    fprintf(output, "Overall statistics\n");
    fprintf(output, "==================\n");
    fprintf(output, "\n- Basic:\n");
    fprintf(output, "\t·Total number of white wins: %-7u (%.2f%%)\n", statistics.white_wins, whiteWinPercentage);
    fprintf(output, "\t·Total number of black wins: %-7u (%.2f%%)\n", statistics.black_wins, blackWinPercentage);
    fprintf(output, "\t·Total winrate             : %.2f%%\n", winRate);
    fprintf(output, "\t·Total number of draws     : %-7u (%.2f%%)\n", statistics.draws, drawPercentage);
    fprintf(output, "\t·Total number of games     : %-7lu\n", statistics.numGames);
    fprintf(output, "\t·Total number of moves     : %-7lu\n", statistics.totalMoveCount);
    fprintf(output, "------------------\n\n");
    fprintf(output, "- Averages:\n");
    fprintf(output, "\t·Average game duration     : %-7.2f seconds\n", statistics.averageGameDuration);
    fprintf(output, "\t·Average PlyCount          : %-7u\n", statistics.averagePlyCount);
    fprintf(output, "\t·Average depth per move    : %-7u\n", statistics.averageDepth);
    fprintf(output, "\t·Average time per move     : %-7.2f seconds\n", statistics.averageTimePerMove);
    fprintf(output, "------------------\n\n");
    fprintf(output, "- ECO Distribution:\n");

    for (int i = 0; i < NUM_ECOS; i++)
    {
        fprintf(output, "\t·ECO %c number of games     : %-7u (%.2f%%)\n", 'A' + i, statistics.ecoCodeGames[i],
                statistics.averageEcoCodes[i]);
    }

    fprintf(output, "==================\n");
}