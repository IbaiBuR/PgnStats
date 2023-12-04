CC=gcc
CFLAGS=-Wall -I.
all: PgnStats
PgnStats: main.o functions.o; $(CC) -o PgnStats main.o functions.o
.PHONY:clean
clean: ;rm -f *.o PgnStats

