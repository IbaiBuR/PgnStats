#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

int main(int argc, char *argv[])
{
  FILE *f_in, *f_out, *stats;
  char nomfich[N];
  
  if(argc < 2)
  {
    printf("Please provide the name of the pgn file you want to process.");
    return 1;
  }

  if(!(f_in=fopen(argv[1],"r")))
  {
    printf("Could not access the input file.");
    return 2;
  }

  if(!(f_out=fopen("out.txt","w")))
  {
    printf("Could not access the output file.");
    fclose(f_in);
    return 3;
  }

  deleteTags(f_in,f_out);
  fclose(f_out);

  if(!(f_out=fopen("out.txt","r")))
  {
    printf("Could not access the specified file.");
    return 4;
  }
  
  strcpy(nomfich,argv[1]);
  char *pospoint = strstr(nomfich, ".");
  *pospoint = '\0';
  strcat(nomfich, ".txt");
  
  if(!(stats=fopen(nomfich,"w")))
  {
    printf("Could not access the specified file.");
    fclose(f_out);
    return 5;
  }

  getstats(f_out, stats);
  getavgGD(f_out, stats);
  getavgPC(f_out, stats);
  getavgD(f_out, stats);
  getavgT(f_out, stats);
  getAvgEco(f_out, stats);

  fclose(f_in);
  fclose(f_out);
  fclose(stats);
  remove("out.txt");
  
  return 0;
}
