#ifndef STATISTICS_H
#define STATISTICS_H

#include <stdio.h>
#include <stdbool.h>
#include "types.h"

void getOverallStats(FILE *, FILE *); //gets some basic statistics of the input pgn file
void getAverageGameDuration(FILE *, FILE *); //gets the average game duration of the input pgn file
void getAveragePlyCount(FILE *, FILE *); //gets the average PlyCount of the input pgn file
void getAverageDepth(FILE *, FILE *); //gets the average depth per move of the input pgn file
void getAvgTimePerMove(FILE *, FILE *); //gets the average time per move of the input pgn file
void getAverageEco(FILE *, FILE *); //gets the average eco code distribution of the input pgn file

#endif