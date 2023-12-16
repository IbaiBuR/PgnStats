#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <stdio.h>
#include "types.h"

void getIndividualStats(FILE *, FILE *); // returns some basic statistics for each player in the PGN file
void printIndividualStats(Players, FILE *, size_t, size_t); // prints the statistics for each player in the PGN file
void getIndividualAverageDepth(FILE *, Players *); // returns the average depth for each player in the PGN file
void getIndividualTotalMoveCount(FILE *, Players *); // returns the total number of moves for each player in the PGN file

#endif