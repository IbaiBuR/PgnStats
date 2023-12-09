#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <stdio.h>
#include "types.h"

void getIndividualStats(FILE *, FILE *); // gets some basic statistics for each player in the file
unsigned * getIndividualAverageDepth(FILE *, Players *); // gets the average depth for each player in the file

#endif