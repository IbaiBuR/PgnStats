cd src
gcc -I C:\msys64\mingw64\include\ncurses -o PgnStats main.c statistics.c util.c individual.c -lncurses -L C:\msys64\mingw64\bin -DNCURSES_STATIC
del *.o