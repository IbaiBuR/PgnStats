#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"
#include "types.h"

void deleteTags(FILE *input, FILE *output)
{
  char line[MAX_MOVES];

  while(fgets(line,sizeof(line),input))
  {
    if(!(strncmp(line, "[Result ", MAX_RESULT_LINE) == 0 || strncmp(line, "[GameStartTime ", MAX_GAME_START_LINE) == 0 || strncmp(line, "[GameEndTime ", MAX_GAME_END_LINE) == 0 ))
      fputs(line, output);
  }

  rewind(input);
}

void getOutputFileName(char *inputFileName, char *outputFileName)
{
    strncpy(outputFileName, inputFileName, FILENAME_LENGTH);
    char *pospoint = strstr(outputFileName, ".");

    if (pospoint != NULL) 
    {
        *pospoint = '\0';
        strncat(outputFileName, ".txt", FILENAME_LENGTH - strlen(outputFileName));
    }
}

bool tagIsPresent(FILE *input, char *tagName)
{
  char buffer[MAX_MOVES];
  bool tagInFile = false;

  while(fgets(buffer, sizeof(buffer), input) && !tagInFile)
  {
    tagInFile = strstr(buffer, tagName);
  }

  rewind(input);

  return tagInFile;
}

bool isFound(char *playerName, char playerNames[MAX_TOTAL_PLAYERS][MAX_PLAYER_NAME_LENGTH])
{
    bool found = false;

    for(int i = 0; i < MAX_TOTAL_PLAYERS && !found; i++)
    {
        if(strcmp(playerName, playerNames[i]) == 0)
            found = true;
    }

    return found;
}