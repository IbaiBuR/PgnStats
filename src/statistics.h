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