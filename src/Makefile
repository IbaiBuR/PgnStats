CC=gcc
CFLAGS=-Wall -I.
all: PgnStats
PgnStats: main.o statistics.o util.o individual.o
	$(CC) $(CFLAGS) -o PgnStats main.o statistics.o util.o individual.o
.PHONY: clean
clean:
	rm -f *.o temporal.pgn