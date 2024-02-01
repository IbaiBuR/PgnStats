# PgnStats
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
## Sample output using a PGN from a [FishTest](https://tests.stockfishchess.org) patch

### Overall statistics

```text
Overall statistics
==================

- Basic:
	·Total number of white wins: 29476   (52.12%)
	·Total number of black wins: 226     (0.40%)
	·Total win rate            : 52.52%
	·Total number of draws     : 26711   (47.23%)
	·Total number of games     : 56554  
	·Total number of moves     : 6613877
------------------

- Averages:
	·Average game duration     : 238.89  seconds
	·Average PlyCount          : 116    
	·Average depth per move    : 24     
	·Average time per move     : 2.04    seconds
------------------

==================
```

*Disclaimer*: The ECO distribution is not shown since FishTest uses EPDs for its tests

### Individual statistics

```text
=====================================

There are exactly 2 players in the PGN file:

- Player: New-aae3e7f478      
	·White wins     : 14704   (26.06%)
	·Black wins     : 114     (0.20%)
	·Draws          : 26711   (47.35%)
	·Lost with white: 112     (0.20%)
	·Lost with black: 14772   (26.19%)
	·Total games    : 56413   (99.75%)
	·Total moves    : 3307001 (50.00%)
	·Win rate       : 26.27%
	·Avg. Depth     : 24     

------------------------------

- Player: Base-061f98a9e3     
	·White wins     : 14772   (26.19%)
	·Black wins     : 112     (0.20%)
	·Draws          : 26711   (47.35%)
	·Lost with white: 114     (0.20%)
	·Lost with black: 14704   (26.06%)
	·Total games    : 56413   (99.75%)
	·Total moves    : 3306876 (50.00%)
	·Win rate       : 26.38%
	·Avg. Depth     : 24     

==============================
```

## Compilation

You need a C compiler such as gcc for example (in PATH) and the ncurses library (installed)

To compile do the following:

git clone the repository and from cmd cd to the folder where you cloned it and run make, or, if you are using Windows, run the windows_compile.bat script.


