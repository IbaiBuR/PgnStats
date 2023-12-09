#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "statistics.h"
#include "util.h"

void getStats(FILE *input, FILE *output)
{
  char line[MAX_MOVES];
  unsigned white_wins = 0, black_wins = 0, draws = 0;
  size_t num_games = 0;

  while(fgets(line,sizeof(line),input))
  {
    if(strstr(line,"1/2-1/2"))
      draws++;
    else if(strstr(line,"1-0"))
      white_wins++;
    else if(strstr(line,"0-1"))
      black_wins++;
  }

  
  rewind(input);

  num_games = numGames(input);
  double whiteWinsPercentage = calculateWhiteWinPercentage(white_wins, num_games);
  double blackWinsPercentage = calculateBlackWinPercentage(black_wins, num_games);
  double drawPercentage = calculateDrawPercentage(draws, num_games);
  double winRate = calculateWinRate(white_wins, black_wins, num_games);

  printf("The total number of games contained in the pgn file is: %lu\n",num_games);
  printf("The number of draws is: %u (%.2f%%)\n",draws, drawPercentage);
  printf("The number of white wins is: %u (%.2f%%)\n",white_wins, whiteWinsPercentage);
  printf("The number of black wins is: %u (%.2f%%)\n",black_wins, blackWinsPercentage);
  printf("The total win rate is: %.2f%%\n", winRate);

  fprintf(output, "The total number of games contained in the pgn file is: %lu\n",num_games);
  fprintf(output, "The number of draws is: %u (%.2f%%)\n",draws, drawPercentage);
  fprintf(output, "The number of white wins is: %u (%.2f%%)\n",white_wins, whiteWinsPercentage);
  fprintf(output, "The number of black wins is: %u (%.2f%%)\n",black_wins, blackWinsPercentage);
  fprintf(output, "The total win rate is: %.2f%%\n", winRate);
}

void getAvgGD(FILE *input, FILE *output)
{
    char buffer[MAX_MOVES];
    double total_duration = 0;

    if (tagIsPresent(input, "[GameDuration "))
    {
        while (fgets(buffer, sizeof(buffer), input))
        {
            if (!(strncmp(buffer, "[GameDuration ", 14)))
            {
                char *duration_string = strtok(buffer, "\"");  // skip the tag
                duration_string = strtok(NULL, "\"");  // get the duration string

                // Parse the duration string to extract the hours, minutes, and seconds
                int hours = atoi(strtok(duration_string, ":"));
                int minutes = atoi(strtok(NULL, ":"));
                int seconds = atoi(strtok(NULL, ":"));

                // Convert the duration to seconds
                double duration = hours * 3600 + minutes * 60 + seconds;

                // Add the duration to the total duration 
                total_duration += duration;
            }
        }
        
      rewind(input);
      double average_duration = total_duration / numGames(input);

      printf("The average game duration is: %.2f seconds\n", average_duration);
      fprintf(output, "The average game duration is: %.2f seconds\n", average_duration);
    }
    else
      printf("The GameDuration tag was not found\n");
    
}

void getAvgPC(FILE *input, FILE *output)
{
  char buffer[MAX_MOVES];
  unsigned total_plycount = 0, plycount, average_plycount;

  if(tagIsPresent(input, "[PlyCount "))
  {
    while(fgets(buffer,sizeof(buffer),input))
    {
      if(strstr(buffer,"[PlyCount "))
      {
        sscanf(buffer, "[PlyCount \"%u\"]", &plycount);
        total_plycount += plycount;
      }
    }
    
    rewind(input);
    average_plycount = total_plycount / numGames(input);
    printf("The average plycount is: %2d\n", average_plycount);
    fprintf(output, "The average plycount is: %2d\n", average_plycount);
  }
  else
    printf("The PlyCount tag was not found\n");

}

void getAvgD(FILE *input, FILE *output)
{
  char buffer[MAX_MOVES];
  unsigned depth, avgdepth, total_depth = 0, move_count = 0;

  while(fgets(buffer,sizeof(buffer),input))
  {
    char *movestart = strstr(buffer,"{");

    if(movestart && !(strstr(buffer,"{book}")))
    {
      sscanf(movestart, "{%*f/%u %*f%*c}", &depth);

      total_depth += depth;
      move_count++;
    }
  }

  rewind(input);

  avgdepth = total_depth / move_count;

  if(avgdepth)
  {
    printf("The average depth per move is: %u\n",avgdepth);
    fprintf(output, "The average depth per move is: %u\n",avgdepth);
  }
  else
    printf("Could not parse the average depth per move\n");
    
}

void getAvgT(FILE *input, FILE *output)
{
	char buffer[MAX_MOVES];
	float time, total_time = 0;
	unsigned move_count = 0;
	double avgtime;

	while(fgets(buffer,sizeof(buffer),input))
	{
		char *movestart = strstr(buffer, "{");
        char *formatting = (char *) malloc (2 * sizeof(char));

		if(movestart && !(strstr(buffer, "{book}")))
		{
			sscanf(movestart, "{%*f/%*u %f%2s}", &time, formatting);

      if(strncmp(formatting, "ms", 2) == 0)
        time /= 1000.0;

			total_time += time; 			
			move_count++;
		}
	}

  rewind(input);
  avgtime = (double)total_time / move_count;
  
  if(avgtime)
  {
    printf("The average time per move is: %.2f seconds \n",avgtime);
    fprintf(output, "The average time per move is: %.2f seconds \n",avgtime);
  }
  else
    printf("Could not parse the average time per move\n");
}

void getAvgEco(FILE *input, FILE *output)
{
  unsigned ECO_CODES[NUM_ECOS] = {0};
  char eco_letter;
  char buffer[MAX_MOVES];
  size_t num_games;

  if(tagIsPresent(input, "[ECO "))
  {
    while(fgets(buffer, sizeof(buffer), input))
    {
      if(strstr(buffer, "[ECO "))
      {
        sscanf(buffer, "[ECO \"%c%*c%*c\"]", &eco_letter);
        ECO_CODES[eco_letter - 'A' + 0]++;
      }
    }

    rewind(input);
    num_games = numGames(input);
    double eco_percentages[5];

    for (int i = 0; i < 5; i++)
      eco_percentages[i] = ((double)ECO_CODES[i]/num_games * 100);
    
    for (int i = 0; i < 5; i++) 
    {
      printf("There are %u eco %c games (%.2f%%)\n", ECO_CODES[i], 'A' + i, eco_percentages[i]);
      fprintf(output, "There are %u eco %c games (%.2f%%)\n", ECO_CODES[i], 'A' + i, eco_percentages[i]);
    }
  }
  else
    printf("The ECO tag was not found\n");
}