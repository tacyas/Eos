#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output:GLImage\n");
    fprintf(stderr, "    [-O[utput]           OutInfo             (stdout    ).as(outFile::ASCII      ) ] :Optional  :Output:Information\n");
    fprintf(stderr, "    [-e[psilon]          epsilon             (2.2e-16   ).as(Real                ) ] :Optional  :SmallValueForLog\n");
    fprintf(stderr, "    [-thres[hold]High    thresHigh           (1.0       ).as(Real                ) ] :Optional  :HighCut\n");
    fprintf(stderr, "    [-thres[hold]Low     thresLow            (0.0       ).as(Real                ) ] :Optional  :LowCut\n");
    fprintf(stderr, "    [-exceptValue        exceptValue         (0.0       ).as(Real                ) ] :Optional  :Except Value\n");
    fprintf(stderr, "    [-range              range               (2.0       ).as(Real                ) ] :Optional  :mean+-range*sd (LowCut-HighCut)\n");
    fprintf(stderr, "    [-nHist              nHist               (8         ).as(Integer             ) ] :Optional  :GrayLevel\n");
    fprintf(stderr, "    [-offset             offset              (1         ).as(Integer             ) ] :Optional  :Distance\n");
    fprintf(stderr, "    [-angle              angleMode           (15        ).as(Integer             ) ] :Optional  :Angle:1-0, 2-45, 4-90, 8-135 for 2D, 2^13-1=8191 for 3D\n");
    fprintf(stderr, "    [-areaX              minAreaX            (0         ).as(Real                ) \n                         maxAreaX            (1.0       ).as(Real                ) ] :Optional  :\n");
    fprintf(stderr, "    [-areaY              minAreaY            (0         ).as(Real                ) \n                         maxAreaY            (1.0       ).as(Real                ) ] :Optional  :\n");
    fprintf(stderr, "    [-areaZ              minAreaZ            (0         ).as(Real                ) \n                         maxAreaZ            (1.0       ).as(Real                ) ] :Optional  :\n");
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
