# PgnStats
Little C program to get some basic stats from a PGN file

This program gets some basic stats from an input pgn file, such as total number of games, wins by white and by black, average game duration, and average plycount.

Usage is (from cmd):

pgnstats.exe file.pgn output.txt

# Compilation

You need a C compiler such as gcc for example (in PATH)

To compile do the following:

git clone the repository and from cmd cd to the folder where you cloned it and run make, or do the following:

gcc -c functions.c

gcc -c main.c

gcc -o pgnstats functions.o main.o

This will create the pgnstats.exe file that can be used from cmd.


