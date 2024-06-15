#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]         mrcInputFileName         ] \n");
    fprintf(stderr, "    [-o[utput]        llDataOutputFileName     ] \n");
    fprintf(stderr, "    [-c[onfig]        configFile               ] \n");
	fprintf(stderr, "    [-l[ayer]         WhichLayer               ]: If -1, then all layer line information is printed \n");
	fprintf(stderr, "    [-m[ode]          mode                     ] \n");
    fprintf(stderr, "                      1 : Total Layer Line\n");
    fprintf(stderr, "                      2 : Layer Line Info\n");
    fprintf(stderr, "                      4 : Layer Line Data Info\n");
    fprintf(stderr, "                      8 : Layer Line For S\n");
    fprintf(stderr, "    [-h                                        ]: Usage Print\n");
    fprintf(stderr, "\n");
    fprintf(stderr, ">>> Configulation File \n");
    fprintf(stderr, "n0 l0 outPutFileName0\n");
    fprintf(stderr, "n1 l1 outPutFileName1\n");
    fprintf(stderr, ".....................\n");
    exit(EXIT_FAILURE);
}
