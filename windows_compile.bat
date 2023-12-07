cd \src
gcc -c main.c functions.c util.c
gcc -o PgnStats main.o functions.o util.o
del *.o
