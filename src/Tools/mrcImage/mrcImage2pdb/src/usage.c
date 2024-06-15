#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (5         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-hi[gh]             h                   (0         ).as(Real                ) ] :Optional  :Value of high threshold. Default is the MAX.\n");
    fprintf(stderr, "    [-lo[w]              l                   (0         ).as(Real                ) ] :Optional  :Value of low threshold. Default is the MIN.\n");
    fprintf(stderr, "    [-L[attice]                                                                    ] :Optional  :Atoms are on lattice points\n");
    fprintf(stderr, "    [-Skip               Skip                (1         ).as(Integer             ) ] :Optional  :Skip atoms.\n");
    fprintf(stderr, "    [-R[andom]           Random              (0         ).as(Real                ) ] :Optional  :Random\n");
    fprintf(stderr, "    [-d[elta]            delta               (0.1       ).as(Real                ) ] :Optional  :Delta to select atoms to avoid too much concentration. Requiers 0-0.5 value. For mode2-4.\n");
    additionalUsage();
}

void
htmlBeforeUsage(char* thisProgram)
{
    fprintf(stderr, "<HTML>\n");
    fprintf(stderr, "<HEAD>\n");
    fprintf(stderr, "<TITLE>%s</TITLE>\n", thisProgram);
    fprintf(stderr, "</HEAD>\n");
    fprintf(stderr, "<BODY>\n");
    fprintf(stderr, "<H1>%s</H1>\n", thisProgram);
    fprintf(stderr, "<H2>Usage</H2>\n");
    fprintf(stderr, "<PRE>\n");
}

void
htmlAfterUsage(char* thisProgram)
{
    fprintf(stderr, "</PRE>\n");
    fprintf(stderr, "</BODY>\n");
    fprintf(stderr, "</HTML>\n");
}