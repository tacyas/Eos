#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: mrcImage\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Optional  :Output: mrcImage\n");
    fprintf(stderr, "    [-o[utput]B          OutB                (NULL      ).as(outFile             ) ] :Optional  :Output: mrcImage:Binary\n");
    fprintf(stderr, "    [-o[utput]L          OutL                (NULL      ).as(outFile             ) ] :Optional  :Output: mrcImage:Label\n");
    fprintf(stderr, "    [-o[utput]A          OutA                (NULL      ).as(outFile             ) ] :Optional  :Output: mrcImage:Aarea\n");
    fprintf(stderr, "    [-O[utputPeakStatics]OutStatics          (stdout    ).as(outFile             ) ] :Optional  :Output as ASCII: Peak statics\n");
    fprintf(stderr, "    [-t[hreshold]        Sigma               (3.0       ).as(Real                ) ] :Optional  :Input: Peak's values are more than t*sigma.\n");
    fprintf(stderr, "    [-T[hreshold]        Threshold           (0.0       ).as(Real                ) ] :Optional  :Input: Peak's values are more than T.\n");
    fprintf(stderr, "    [-a[rea]             Area                (6.0       ).as(Real                ) ] :Optional  :Input[A^2]: Peak's area are more than a.\n");
    fprintf(stderr, "    [-A[rea]             AreaPixel           (9         ).as(Real                ) ] :Optional  :Input[pixel^2]: Peak's area are more than A.\n");
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
