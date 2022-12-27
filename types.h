#ifndef TYPES_H
#define TYPES_H

 #define MAX_MOVES 1024
 #define N 50
 void getsats(FILE *); //gets some stadistics of the input pgn file
 void deleRtag(FILE *, FILE *); //deletes the result tag of the input pgn file and writes the output to another file
 void getavgGD(FILE *); //gets the average game duration of the input pgn file
 void getavgPC(FILE *); //gets the average PlyCount of the input pgn file

#endif
