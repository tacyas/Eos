#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output: Filtered Image\n");
    fprintf(stderr, "    [-IQ                 IQ                  (NULL      ).as(outFile             ) ] :Optional  :Output: IQ Map\n");
    fprintf(stderr, "    [-vx                 vx                  (0         ).as(Real                ) ] :Optional  :Vector(x)\n");
    fprintf(stderr, "    [-vy                 vy                  (0         ).as(Real                ) ] :Optional  :Vector(y)\n");
    fprintf(stderr, "    [-v1                 v1x                 (0         ).as(Real                ) \n                         v1y                 (0         ).as(Real                ) ] :Optional  :Vector(v1)\n");
    fprintf(stderr, "    [-v2                 v2x                 (0         ).as(Real                ) \n                         v2y                 (0         ).as(Real                ) ] :Optional  :Vector(v2)\n");
    fprintf(stderr, "    [-sx                 sx                  (1         ).as(Integer             ) ] :Optional  :Size(x)\n");
    fprintf(stderr, "    [-sy                 sy                  (1         ).as(Integer             ) ] :Optional  :Size(y)\n");
    fprintf(stderr, "    [-neg[lect]F00                                                                 ] :Optional  :Neglect F00\n");
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
