#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-r[eference]        In2                 (NULL      ).as(inFile              ) ] :Optional  :For Mode1=1 only:ReferenceDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :\n Mode1 \t 0:AutoCorrelation \n\t 1:CrossCorrelation\n");
    fprintf(stderr, "    [-M[ode]             mode2               (0         ).as(Integer             ) ] :Optional  :\n Mode2 \t 0:All is to be calculated.\n\t 1:Pick up at random \n\t 2:Calculate only Omega=0,Alpha=0 \n");
    fprintf(stderr, "    [-n[umber]           number              (NULL      ).as(Integer             ) ] :Optional  :For mode 1 only. Number of points to pick up at random. Defalt:Data size along z axis of inputfile / 10 \n");
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
