#ifndef TYPES_H
#define TYPES_H

#define FILENAME_LENGTH 50
#define NUM_ECOS 5
#define CURRENT_PLAYERS_SIZE 2
#define MAX_MOVES 4096
#define MAX_RESULT_LINE 8
#define MAX_GAME_START_LINE 15
#define MAX_GAME_END_LINE 12
#define MAX_PLAYER_NAME_LENGTH 250
#define MAX_TOTAL_PLAYERS 100

#define FIND_MOVESTART(buffer) strstr(buffer, "{")
#define BOOKMOVE(buffer) strstr(buffer, "{book}")

typedef struct Players
{
    char     playerNames[MAX_TOTAL_PLAYERS][MAX_PLAYER_NAME_LENGTH];
    unsigned individualWhiteWins[MAX_TOTAL_PLAYERS];
    unsigned individualBlackWins[MAX_TOTAL_PLAYERS];
    unsigned individualDraws[MAX_TOTAL_PLAYERS];
    size_t totalPlayerGames[MAX_TOTAL_PLAYERS];
    unsigned individualAverageDepth[MAX_TOTAL_PLAYERS];
    unsigned totalPlayers; 
} Players;

#endif
