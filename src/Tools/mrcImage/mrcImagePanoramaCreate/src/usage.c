#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-I[nput]            In                  (stdin     ).as(inFileList          ) ] :Essential :Input:FileList[mrcImage x y z]\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output:mrcImage\n");
    fprintf(stderr, "    [-o[utput]C[ount]    Count               (NULL      ).as(outFile             ) ] :Optional  :Output(Count):mrcImage\n");
    fprintf(stderr, "    [-N                  Nx                  (0         ).as(Integer             ) \n                         Ny                  (0         ).as(Integer             ) \n                         Nz                  (0         ).as(Integer             ) ] :Optional  :Input:OutImageSize\n");
    fprintf(stderr, "    [-M[ode]             InterpolationMode   (0         ).as(Integer             ) ] :Optional  :InterpolationMode\n");
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
