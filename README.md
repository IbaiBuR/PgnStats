# PgnStats
___
## Overview

PgnStats is a little C program that calculates some basic statistics (both overall and individual) from an input (commented & cutechess-like) pgn file, such as:
- Total number of games
- Total number of wins (by white and black) and draws
- Total number of moves
- Total win rate
- Average game duration
- Average PlyCount
- Average depth
- Average time per move
- ECO Code Distribution

## Usage (from Windows CMD or Linux terminal)

To use this tool you'll need a <b><u>commented</u></b> pgn file which includes the PlyCount, GameDuration and ECO tags, because if not it won't get some stats!

The command you need to apply is:

For <u>Windows</u>:
```
PgnStats.exe <name_of_your_pgn_file>.pgn
```
For <u>Linux</u>:
```
./PgnStats <name_of_your_pgn_file>.pgn
```
## Sample output using a 60000+ games PGN

### Overall statistics

```text
Overall statistics
==================

- Basic:
	·Total number of white wins: 5430    (8.58%)
	·Total number of black wins: 826     (1.30%)
	·Total winrate             : 9.88%
	·Total number of draws     : 57062   (90.12%)
	·Total number of games     : 63320  
	·Total number of moves     : 7726357
------------------

- Averages:
	·Average game duration     : 214.03 seconds
	·Average PlyCount          : 122    
	·Average depth per move    : 29     
	·Average time per move     : 1.93 seconds
------------------

- ECO Distribution:
	·ECO A number of games     : 17245   (27.23%)
	·ECO B number of games     : 12979   (20.50%)
	·ECO C number of games     : 15000   (23.69%)
	·ECO D number of games     : 6674    (10.54%)
	·ECO E number of games     : 11422   (18.04%)
==================
```

### Individual statistics

```text
Individual statistics for each player
=====================================

There are exactly 3 players in the PGN file:

- Player: Eman                
	·White wins : 3094  (4.89%)
	·Black wins : 471   (0.74%)
	·Draws      : 57062 (90.12%)
	·Total games: 63318 (100.00%)
	·Win rate   : 5.63%
	·Avg. Depth : 30   

------------------------------

- Player: ShashChess          
	·White wins : 1104  (3.49%)
	·Black wins : 161   (0.51%)
	·Draws      : 28235 (89.18%)
	·Total games: 31660 (50.00%)
	·Win rate   : 4.00%
	·Avg. Depth : 26   

------------------------------

- Player: BrainLearn          
	·White wins : 1232  (3.89%)
	·Black wins : 194   (0.61%)
	·Draws      : 28827 (91.06%)
	·Total games: 31658 (50.00%)
	·Win rate   : 4.50%
	·Avg. Depth : 30   

==============================
```

## Compilation

You need a C compiler such as gcc for example (in PATH) and the ncurses library (installed)

To compile do the following:

git clone the repository and from cmd cd to the folder where you cloned it and run make, or, if you are using Windows, run the windows_compile.bat script.


