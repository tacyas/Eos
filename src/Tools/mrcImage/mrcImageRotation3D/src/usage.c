#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: mrc\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output: mrc\n");
    fprintf(stderr, "    [-E[uler]A[ngle]     EulerAngle          (YOYS      ).as(String              ) \n                         Rot1                (0.0       ).as(Real                ) \n                         Rot2                (0.0       ).as(Real                ) \n                         Rot3                (0.0       ).as(Real                ) ] :Optional  :Input: Euler Angle\n");
    fprintf(stderr, "    [-N                  Nx                  (-1        ).as(Integer             ) \n                         Ny                  (-1        ).as(Integer             ) \n                         Nz                  (-1        ).as(Integer             ) ] :Optional  :OutputImageSize\n");
    fprintf(stderr, "    [-M[ode]             Mode                (2         ).as(Integer             ) ] :Optional  :InterpolationMode\n");
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
