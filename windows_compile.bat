cd \src
gcc -c main.c statistics.c util.c
gcc -o PgnStats main.o statistics.o util.o
del *.o
