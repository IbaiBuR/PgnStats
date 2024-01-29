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

#pragma once

#include <stdio.h>
#include "types.h"

void getIndividualStats(FILE *, FILE *); // returns some basic statistics for each player in the PGN file
void printIndividualStats(Players, FILE *, size_t, size_t); // prints the statistics for each player in the PGN file
void getIndividualAverageDepth(FILE *, Players *); // returns the average depth for each player in the PGN file
void getIndividualTotalMoveCount(FILE *, Players *); // returns the total number of moves for each player in the PGN file
