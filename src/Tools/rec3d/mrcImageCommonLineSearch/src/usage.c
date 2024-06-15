#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: mrc\n");
    fprintf(stderr, "    [-r[ef]              Ref                 (NULL      ).as(inFile              ) ] :Essential :Input: ref\n");
    fprintf(stderr, "    [-dtheta             dtheta              (1.0       ).as(Real                ) ] :Optional  :Input: degree\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output: OptimalParameter\n");
    fprintf(stderr, "    [-O[utput]           Out2                (NULL      ).as(outFile             ) ] :Optional  :Output: ParameterImage\n");
    fprintf(stderr, "    [-M[ode]             searchMode          (1         ).as(Integer             ) ] :Optional  :SearchMode\n");
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
