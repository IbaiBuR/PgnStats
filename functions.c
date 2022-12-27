#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

void deleteRtag(FILE *input, FILE *output)
{
  char line[MAX_MOVES];

  while(fgets(line,sizeof(line),input))
  {
    if (strncmp(line, "[Result ", 8) == 0) {
      continue;
    }

    // Otherwise, write the line to the output file
    fputs(line, output);
  }
}

void getstats(FILE *data)
{
  char line[MAX_MOVES];
  unsigned num_games = 0, white_wins = 0, black_wins = 0, draws = 0;

  while(fgets(line,sizeof(line),data))
  {
    if(strstr(line,"[Event "))
      num_games++;
    else if(strstr(line,"1/2-1/2"))
      draws++;
    else if(strstr(line,"1-0"))
      white_wins++;
    else if(strstr(line,"0-1"))
      black_wins++;
  }

  printf("The total number of games contained in the pgn file is: %u\n",num_games);
  printf("The number of draws is: %u\n",draws);
  printf("The number of white wins is: %u\n",white_wins);
  printf("The number of black wins is: %u\n",black_wins);
}

void getavgGD(FILE *data)
{
  char buffer[MAX_MOVES];
  double total_duration = 0;
  unsigned num_games = 0;

  while(fgets(buffer,sizeof(buffer),data))
  {
    if(strstr(buffer,"[Event "))
      num_games++;

    else if(!(strncmp(buffer, "[GameDuration ", 14)))
    {
      char *duration_string = strtok(buffer, "\"");  // skip the tag
      duration_string = strtok(NULL, "\"");  // get the duration string

      // Parse the duration string to extract the hours, minutes, and seconds
      int hours = atoi(strtok(duration_string, ":"));
      int minutes = atoi(strtok(NULL, ":"));
      int seconds = atoi(strtok(NULL, ":"));

      // Convert the duration to seconds
      double duration = hours * 3600 + minutes * 60 + seconds;

      // Add the duration to the total duration and increment the number of games
      total_duration += duration;
    }
  }

  double average_duration = total_duration / num_games;
  printf("The average game duration is: %.2f seconds\n", average_duration);
}

void getavgPC(FILE *data)
{
  char buffer[MAX_MOVES];
  unsigned total_plycount = 0, total_games = 0, plycount;
  double average_plycount;

  while(fgets(buffer,sizeof(buffer),data))
  {
    if(strstr(buffer,"[PlyCount "))
    {
      total_games++;
      if(sscanf(buffer, "[PlyCount \"%d\"]", &plycount))
      {
        total_plycount += plycount;
      }
    }
  }

  if(total_games)
  {
    average_plycount = (double)total_plycount / total_games;
    printf("The average plycount: %.2f\n", average_plycount);
  }
  else
    printf("No games found\n");

}
