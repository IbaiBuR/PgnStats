#ifndef TYPES_H
#define TYPES_H

 #include <stdbool.h>
 #include <stdio.h>

 #define MAX_MOVES 4096
 #define N 50
 
 void getstats(FILE *, FILE *); //gets some stadistics of the input pgn file
 void deleteTags(FILE *, FILE *); //deletes the result tag of the input pgn file and writes the output to another file
 void getavgGD(FILE *, FILE *); //gets the average game duration of the input pgn file
 void getavgPC(FILE *, FILE *); //gets the average PlyCount of the input pgn file
 void getavgD(FILE *, FILE *); //gets the average depth per move of the input pgn file
 void getavgT(FILE *, FILE *); //gets the average time per move of the input pgn file
 void getAvgEco(FILE *, FILE *); //gets the average eco code distribution of the inpit pgn file
 size_t numGames(FILE *); //returns the total number of games in the PGN file
 bool tagIsPresent(FILE *, char *); //returns true if the specified tagName is found in the PGN file, otherwise it returns false

#endif
