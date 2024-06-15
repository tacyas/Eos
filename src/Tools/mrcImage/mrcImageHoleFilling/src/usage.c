#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input(0:black, positive:white)\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile::mrcImage   ) ] :Essential :Output(0:black, 1:white\n");
    fprintf(stderr, "    [-n[eighbor]         Neighbor            (8         ).as(Integer             ) ] :Optional  :Neighbor(Black)\n");
    fprintf(stderr, "    [-b[lack]A[rea]      BlackArea           (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output:BlackArea\n");
    fprintf(stderr, "    [-b[lack]L[abel]     BlackLabel          (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output:BlackLabel\n");
    fprintf(stderr, "    [-b[lack]            Black               (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output:Black\n");
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
