# PgnStats
Little C program to get some basic stats from a PGN file

This program gets some basic stats from an input (commented, cutechess-like) pgn file, such as total number of games, wins by white and by black, average game duration, average plycount and average depth and time per move.

# Usage (from cmd)

To use this tool you need a commented pgn file which includes the PlyCount tag and the GameDuration tag too, because if not it wont get those two stats!

The command you need to apply is:<p>

PgnStats.exe <name_of_your_pgn>.pgn

## Sample output 

```
The total number of games contained in the pgn file is: 24000
The number of draws is: 20251 (84.38%)
The number of white wins is: 3629 (15.12%)
The number of black wins is: 119 (0.50%)
The average game duration is: 228.04 seconds
The average plycount is: 136
The average depth per move is: 28
The average time per move is: 1.87 seconds 
There are 6000 eco A games (25.00%)
There are 8000 eco B games (33.33%)
There are 6000 eco C games (25.00%)
There are 2000 eco D games (8.33%)
There are 2000 eco E games (8.33%)
```

# Compilation

You need a C compiler such as gcc for example (in PATH)

To compile do the following:

git clone the repository and from cmd cd to the folder where you cloned it and run make, or, if you are using Windows, run the windows_compile.bat script.


