#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (stdin     ).as(inFile              ) ] :Optional  :Input:\n");
    fprintf(stderr, "    [-a[Axis]            ax                  (2         ).as(Real                ) \n                         ay                  (3         ).as(Real                ) \n                         az                  (0         ).as(Real                ) ] :Optional  :Input:\n");
    fprintf(stderr, "    [-b[Axis]            bx                  (2         ).as(Real                ) \n                         by                  (3         ).as(Real                ) \n                         bz                  (0         ).as(Real                ) ] :Optional  :Input:\n");
    fprintf(stderr, "    [-c[Axis]            cx                  (2         ).as(Real                ) \n                         cy                  (3         ).as(Real                ) \n                         cz                  (1         ).as(Real                ) ] :Optional  :Input:\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output:\n");
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