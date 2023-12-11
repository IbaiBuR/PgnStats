cd src
x86_64-w64-mingw32-gcc -I/usr/x86_64-w64-mingw32/sys-root/mingw/include/ -o PgnStats main.c statistics.c util.c individual.c -static -lncursesw -L/usr/x86_64-w64-mingw32/sys-root/mingw/bin/ -DNCURSES_STATIC
mv PgnStats.exe ../binaries
make clean
