#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-O[utput]           OutMRC              (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile(mrcImage)\n");
    fprintf(stderr, "    [-n                  N                   (100       ).as(Integer             ) ] :Optional  :number\n");
    fprintf(stderr, "    [-a[verage]          Ave                 (0.0       ).as(Real                ) ] :Optional  :average\n");
    fprintf(stderr, "    [-sd                 SD                  (1.0       ).as(Real                ) ] :Optional  :SD\n");
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
