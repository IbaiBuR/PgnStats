#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

void deleteTags(FILE *input, FILE *output)
{
  char line[MAX_MOVES];

  while(fgets(line,sizeof(line),input))
  {
    if(strncmp(line, "[Result ", 8) == 0 || strncmp(line, "[GameStartTime ", 15) == 0 || strncmp(line, "[GameEndTime ", 12) == 0 ) {
      continue;
    }

    // Otherwise, write the line to the output file
    fputs(line, output);
  }

  rewind(input);
}

void getstats(FILE *input, FILE *output)
{
  char line[MAX_MOVES];
  unsigned num_games = 0, white_wins = 0, black_wins = 0, draws = 0;

  while(fgets(line,sizeof(line),input))
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

  
  rewind(input);

  printf("The total number of games contained in the pgn file is: %u\n",num_games);
  printf("The number of draws is: %u (%.2f%%)\n",draws, ((double)draws/num_games)*100);
  printf("The number of white wins is: %u (%.2f%%)\n",white_wins, ((double)white_wins/num_games)*100);
  printf("The number of black wins is: %u (%.2f%%)\n",black_wins, ((double)black_wins/num_games)*100);

  fprintf(output, "The total number of games contained in the pgn file is: %u\n",num_games);
  fprintf(output, "The number of draws is: %u (%.2f%%)\n",draws, ((double)draws/num_games)*100);
  fprintf(output, "The number of white wins is: %u (%.2f%%)\n",white_wins, ((double)white_wins/num_games)*100);
  fprintf(output, "The number of black wins is: %u (%.2f%%)\n",black_wins, ((double)black_wins/num_games)*100);
}

void getavgGD(FILE *input, FILE *output)
{
  char buffer[MAX_MOVES];
  double total_duration = 0;
  unsigned num_games = 0;

  while(fgets(buffer,sizeof(buffer),input))
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
 
  rewind(input);

  double average_duration = total_duration / num_games;
  printf("The average game duration is: %.2f seconds\n", average_duration);
  fprintf(output, "The average game duration is: %.2f seconds\n", average_duration);
}

void getavgPC(FILE *input, FILE *output)
{
  char buffer[MAX_MOVES];
  unsigned total_plycount = 0, total_games = 0, plycount, average_plycount;

  while(fgets(buffer,sizeof(buffer),input))
  {
    if(strstr(buffer,"[PlyCount "))
    {
      total_games++;
      if(sscanf(buffer, "[PlyCount \"%u\"]", &plycount))
      {
        total_plycount += plycount;
      }
    }
  }

  if(total_games)
  {
    average_plycount = total_plycount / total_games;
    printf("The average plycount is: %2d\n", average_plycount);
    fprintf(output, "The average plycount is: %2d\n", average_plycount);
  }
  else
    printf("The PlyCount tag was not found\n");

  rewind(input);
}

void getavgD(FILE *input, FILE *output)
{
  char buffer[MAX_MOVES];
  unsigned depth, avgdepth, total_depth = 0, move_count = 0;

  while(fgets(buffer,sizeof(buffer),input))
  {
    char *movestart = strstr(buffer,"{");

    if(movestart && !(strstr(buffer,"{book}")))
    {
      sscanf(movestart, "{%*f/%u %*f%*c}", &depth);
      // Add the depth to the total depth
      total_depth += depth;
      move_count++;
    }
  }

  rewind(input);
  avgdepth = total_depth / move_count;
  printf("The average depth per move is: %u\n",avgdepth);
  fprintf(output, "The average depth per move is: %u\n",avgdepth);
}

void getavgT(FILE *input, FILE *output)
{
	char buffer[MAX_MOVES];
	float time, total_time = 0;
	unsigned move_count = 0;
	double avgtime;

	while(fgets(buffer,sizeof(buffer),input))
	{
		char *movestart = strstr(buffer, "{");

		if(movestart && !(strstr(buffer, "{book}")))
		{
			sscanf(movestart, "{%*f/%*u %f%*c}", &time);
			//Add time to the total time
			total_time += time;
			move_count++;
		}
	}

  rewind(input);
	avgtime = (double)total_time / move_count;
	printf("The average time per move is: %.2f seconds \n",avgtime);
	fprintf(output, "The average time per move is: %.2f seconds \n",avgtime);
}

size_t numGames(FILE *input)
{
  char lines[MAX_MOVES];
  size_t games = 0;

  while(fgets(lines, sizeof(lines), input))
  {
    if(strstr(lines, "[Event "))
      games++;
  }

  rewind(input);

  return games;
}

void getAvgEco(FILE *input, FILE *output)
{
  unsigned ECO_CODES[5];
  char eco_letter, buffer[MAX_MOVES];
  
  while(fgets(buffer, sizeof(buffer), input))
  {
    if(strstr(buffer, "[ECO "))
    {
      sscanf(buffer, "[ECO \"%c%*c%*c\"]", &eco_letter);
      ECO_CODES[eco_letter - 'A' + 0]++;
    }
  }

  rewind(input);
  
  printf("There are %u eco A openings (%.2f%%)", ECO_CODES[0], ((double)ECO_CODES[0]/numGames(input) * 100));
  printf("There are %u eco B openings (%.2f%%)", ECO_CODES[1], ((double)ECO_CODES[1]/numGames(input) * 100));
  printf("There are %u eco C openings (%.2f%%)", ECO_CODES[2], ((double)ECO_CODES[2]/numGames(input) * 100));
  printf("There are %u eco D openings (%.2f%%)", ECO_CODES[3], ((double)ECO_CODES[3]/numGames(input) * 100));
  printf("There are %u eco E openings (%.2f%%)", ECO_CODES[4], ((double)ECO_CODES[4]/numGames(input) * 100));

  fprintf(output, "There are %u eco A openings (%.2f%%)", ECO_CODES[0], ((double)ECO_CODES[0]/numGames(input) * 100));
  fprintf(output, "There are %u eco B openings (%.2f%%)", ECO_CODES[1], ((double)ECO_CODES[1]/numGames(input) * 100));
  fprintf(output, "There are %u eco C openings (%.2f%%)", ECO_CODES[2], ((double)ECO_CODES[2]/numGames(input) * 100));
  fprintf(output, "There are %u eco D openings (%.2f%%)", ECO_CODES[3], ((double)ECO_CODES[3]/numGames(input) * 100));
  fprintf(output, "There are %u eco E openings (%.2f%%)", ECO_CODES[4], ((double)ECO_CODES[4]/numGames(input) * 100));
  
}
