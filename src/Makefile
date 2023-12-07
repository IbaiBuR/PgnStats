CC=gcc
CFLAGS=-Wall -I.
all: PgnStats
PgnStats: main.o functions.o util.o; $(CC) -o PgnStats main.o functions.o util.o
.PHONY:clean
clean: ;rm -f *.o