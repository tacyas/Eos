#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::Array       ) ] :Essential :Input:Moving\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile::ASCII      ) ] :Optional  :Output\n");
    fprintf(stderr, "    [-O[utput]           OutName             (Movie_%%04d.mrc).as(String              ) ] :Optional  :Output\n");
    fprintf(stderr, "    [-n                  Num                 (10        ).as(Integer             ) ] :Optional  :numberOfMovie\n");
    fprintf(stderr, "    [-N                  Nx                  (256       ).as(Integer             ) \n                         Ny                  (256       ).as(Integer             ) \n                         Nz                  (256       ).as(Integer             ) ] :Optional  :Output:mrcImageSize\n");
    fprintf(stderr, "    [-L                  Lx                  (1.0       ).as(Real                ) \n                         Ly                  (1.0       ).as(Real                ) \n                         Lz                  (1.0       ).as(Real                ) ] :Optional  :Output:mrcImageLength\n");
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
