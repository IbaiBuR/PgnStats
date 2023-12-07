CC=gcc
CFLAGS=-Wall -I.
all: PgnStats
PgnStats: main.o statistics.o util.o
	$(CC) $(CFLAGS) -o PgnStats main.o statistics.o util.o
.PHONY: clean
clean:
	rm -f *.o