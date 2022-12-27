#ifndef TYPES_H
#define TYPES_H

 #define MAX_MOVES 1024
 #define N 50
 void getstats(FILE *, FILE *); //gets some stadistics of the input pgn file
 void deleteTags(FILE *, FILE *); //deletes the result tag of the input pgn file and writes the output to another file
 void getavgGD(FILE *, FILE *); //gets the average game duration of the input pgn file
 void getavgPC(FILE *, FILE *); //gets the average PlyCount of the input pgn file
 void getavgD(FILE *, FILE *); //gets the average depth per move of the input pgn file
 void getavgT(FILE *, FILE *); //gets the average time per move of the input pgn file

#endif
