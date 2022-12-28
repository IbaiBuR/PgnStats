CC=gcc
CFLAGS=-I.
pgnstats: main.o functions.o; $(CC) -o pgnstats main.o functions.o
.PHONY:clean
clean: ;rm -f *.o

