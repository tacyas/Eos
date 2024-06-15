#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: MRC\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output: MRC\n");
    fprintf(stderr, "    [-times              times               (1         ).as(Integer             ) ] :Optional  :Times: erosion*times -> dilation*times\n");
    fprintf(stderr, "    [-o[utput]SE         OutSE               (NULL      ).as(outFile             ) ] :Optional  :Output: MRC(SE)\n");
    fprintf(stderr, "    [-S[tructuring]E[lement]SEmode              (0         ).as(Integer             ) ] :Optional  :StructuringElement\n");
    fprintf(stderr, "    [-r[adius]           radius              (2         ).as(Integer             ) ] :Optional  :Radius\n");
    fprintf(stderr, "    [-n                  n                   (5         ).as(Integer             ) ] :Optional  :size\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
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