#ifndef STATISTICS_H
#define STATISTICS_H

#include <stdio.h>
#include <stdbool.h>
#include "types.h"

void getOverallStats(FILE *, FILE *); // returns some basic statistics of the input PGN file
void getAverageGameDuration(FILE *, Statistics *); // returns the average game duration of the input PGN file
void getAveragePlyCount(FILE *, Statistics *); // returns the average PlyCount of the input PGN file
void getAverageDepth(FILE *, Statistics *); // returns the average depth per move of the input PGN file
void getAverageTimePerMove(FILE *, Statistics *); // returns the average time per move of the input PGN file
void getAverageEco(FILE *, Statistics *); // returns the average eco code distribution of the input PGN file
void printOverallStats(Statistics, FILE *); // prints the overall statistics calculated for the input PGN file

#endif