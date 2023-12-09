cd \src
gcc -c main.c statistics.c util.c individual.c
gcc -o PgnStats main.o statistics.o util.o individual.o
del *.o
