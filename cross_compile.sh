cd src
x86_64-w64-mingw32-gcc -o PgnStats main.c statistics.c util.c individual.c -lncursesw -DNCURSES_STATIC
mv PgnStats.exe ../binaries
make clean
