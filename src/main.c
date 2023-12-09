#include <stdio.h>
#include "types.h"
#include "util.h"
#include "statistics.h"

int main(int argc, char *argv[])
{
  FILE *f_in, *f_out, *stats;
  char nomfich[FILENAME_LENGTH];
  
  if(argc < 2)
  {
    printf("Please provide the name of the pgn file you want to process.\n");
    return 1;
  }

  if(!(f_in=fopen(argv[1],"r")))
  {
    printf("Could not access the input file.\n");
    return 2;
  }

  if(!(f_out=fopen("out.txt","w")))
  {
    printf("Could not access the output file.\n");
    fclose(f_in);
    return 3;
  }

  deleteTags(f_in,f_out);
  fclose(f_out);

  if(!(f_out=fopen("out.txt","r")))
  {
    printf("Could not access the specified file.\n");
    return 4;
  }
  
  getOutputFileName(argv[1],nomfich);
  
  if(!(stats=fopen(nomfich,"w")))
  {
    printf("Could not access the specified file.\n");
    fclose(f_out);
    return 5;
  }

  getStats(f_out, stats);
  getAvgGD(f_out, stats);
  getAvgPC(f_out, stats);
  getAvgD(f_out, stats);
  getAvgT(f_out, stats);
  getAvgEco(f_out, stats);

  fclose(f_in);
  fclose(f_out);
  fclose(stats);
  
  remove("out.txt");
  
  return 0;
}
