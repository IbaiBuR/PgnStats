#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

int main(int argc, char *argv[])
{
  FILE *f_in, *f_out, *stats;
  if(argc < 3)
  {
    printf("Please provide the name of the pgn file you want to process.");
    return 1;
  }

  if(!(f_in=fopen(argv[1],"r")))
  {
    printf("Could not access the input file.");
    return 2;
  }

  if(!(f_out=fopen(argv[2],"w")))
  {
    printf("Could not access the output file.");
    fclose(f_in);
    return 3;
  }

  deleteRtag(f_in,f_out);
  fclose(f_out);

  if(!(f_out=fopen(argv[2],"r")))
  {
    printf("Could not access the specified file.");
    return 4;
  }
  
  if(!(stats=fopen("stats.txt","w")))
  {
    printf("Could not access the specified file.");
    fclose(f_out);
    return 5;
  }

  getstats(f_out, stats);
  rewind(f_out);
  getavgGD(f_out, stats);
  rewind(f_out);
  getavgPC(f_out, stats);
  rewind(f_out);
  getavgD(f_out, stats);
  rewind(f_out);
  getavgT(f_out, stats);

  fclose(f_in);
  fclose(f_out);
  fclose(stats);

  return 0;
}
