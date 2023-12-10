#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "util.h"
#include "statistics.h"
#include "individual.h"

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

int main(int argc, char *argv[])
{
    FILE *f_in, *f_out, *stats, *individualStats;
    initscr();

    if (argc < 2)
    {
        printw("Please provide the name of the pgn file you want to process.\n");
        return EXIT_FAILURE;
    }

    if (!(f_in = fopen(argv[1], "r")))
    {
        printw("Could not access the input file.\n");
        return EXIT_FAILURE + 1;
    }

    if (!(f_out = fopen(TEMPORAL_PGN, "w")))
    {
        printw("Could not access the output file.\n");
        fclose(f_in);
        return EXIT_FAILURE + 2;
    }

    deleteTags(f_in, f_out);
    fclose(f_out);

    if (!(f_out = fopen(TEMPORAL_PGN, "r")))
    {
        printw("Could not access the specified file.\n");
        return EXIT_FAILURE + 3;
    }

    if (!(stats = fopen(OVERALL_STATS_FILE_NAME, "w")))
    {
        printw("Could not access the specified file.\n");
        fclose(f_out);
        return EXIT_FAILURE + 4;
    }

    if (!(individualStats = fopen(INDIVIDUAL_STATS_FILE_NAME, "w")))
    {
        printw("Could not access the specified file.\n");
        fclose(f_out);
        fclose(stats);
        return EXIT_FAILURE + 5;
    }

    addstr("Calculating overall statistics...\n");
    refresh();
    getOverallStats(f_out, stats);
    addstr("Calculating individual statistics...\n");
    refresh();
    getIndividualStats(f_out, individualStats);

    fclose(f_in);
    fclose(f_out);
    fclose(stats);
    fclose(individualStats);

    remove(TEMPORAL_PGN);

    addstr("Statistics calculation finished, press any key to exit...\n");
    refresh();
    getch();
    endwin();

    return EXIT_SUCCESS;
}
