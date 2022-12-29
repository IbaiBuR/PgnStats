CC=gcc
CFLAGS=-I.
PgnStats: main.o functions.o; $(CC) -o PgnStats main.o functions.o
.PHONY:clean
clean: ;rm -f *.o

