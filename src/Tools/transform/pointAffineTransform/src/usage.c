#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-p[oint]            X                   (0         ).as(Real                ) \n                         Y                   (0         ).as(Real                ) \n                         Z                   (0         ).as(Real                ) ] :Essential :Input: Points\n");
    fprintf(stderr, "    [-Euler              Euler               (YOYS      ).as(String              ) \n                         Rot1                (0         ).as(Real                ) \n                         Rot2                (0         ).as(Real                ) \n                         Rot3                (0         ).as(Real                ) ] :Optional  :Input: EuerAngle\n");
    fprintf(stderr, "    [-shift              dX                  (0         ).as(Real                ) \n                         dY                  (0         ).as(Real                ) \n                         dZ                  (0         ).as(Real                ) ] :Optional  :Input: shift[pixel]\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
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
