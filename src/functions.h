#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>

void getStats(FILE *, FILE *); //gets some basic statistics of the input pgn file
void deleteTags(FILE *, FILE *); //deletes the result tag of the input pgn file and writes the output to another file
void getAvgGD(FILE *, FILE *); //gets the average game duration of the input pgn file
void getAvgPC(FILE *, FILE *); //gets the average PlyCount of the input pgn file
void getAvgD(FILE *, FILE *); //gets the average depth per move of the input pgn file
void getAvgT(FILE *, FILE *); //gets the average time per move of the input pgn file
void getAvgEco(FILE *, FILE *); //gets the average eco code distribution of the inpit pgn file
void getOutputFileName(char *, char *); //gets the output txt file name based on the input pgn file name
size_t numGames(FILE *); //returns the total number of games in the PGN file
bool tagIsPresent(FILE *, char *); //returns true if the specified tagName is found in the PGN file, otherwise it returns false

#endif