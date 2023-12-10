CC=gcc
CFLAGS=-Wall -I.
LDFLAGS = -lncurses

all: PgnStats
PgnStats: main.o statistics.o util.o individual.o
	$(CC) $(CFLAGS) -o PgnStats main.o statistics.o util.o individual.o $(LDFLAGS)
.PHONY: clean
clean:
	rm -f *.o temporal.pgn