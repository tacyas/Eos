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
    fprintf(stderr, "    [-a[xisOrder]        ax                  (1         ).as(Integer             ) \n                         ay                  (2         ).as(Integer             ) \n                         az                  (3         ).as(Integer             ) ] :Optional  :AxisOrder\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-m[ode]m[rcimage]   mm                  (2         ).as(Integer             ) ] :Optional  :Mode of mrcImage\n");
    fprintf(stderr, "    [-l[ength]m[rcimage] lm                  (0         ).as(Real                ) ] :Optional  :Length of mrcImage\n");
    fprintf(stderr, "    [-l[ength]m[rcimage]3lmx                 (0         ).as(Real                ) \n                         lmy                 (0         ).as(Real                ) \n                         lmz                 (0         ).as(Real                ) ] :Optional  :Length of mrcImage\n");
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
