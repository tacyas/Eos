#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Test: Input\n");
    fprintf(stderr, "    [-r[ef]              Ref                 (NULL      ).as(inFile              ) ] :Essential :Reference: Input\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :NormalizedImage:  Output\n");
    fprintf(stderr, "    [-O[utput]           OutParam            (stdout    ).as(outFile             ) ] :Optional  :Parameters:       Output\n");
    fprintf(stderr, "    [-D[ataForNormalizing]UsedData            (stdout    ).as(outFile             ) ] :Optional  :DataList to be used\n");
    fprintf(stderr, "    [-Cylinder           CCenterX            (20        ).as(Real                ) \n                         CCenterY            (20        ).as(Real                ) \n                         CMinR               (10        ).as(Real                ) \n                         CMaxR               (20        ).as(Real                ) ] :Optional  :Cylinder Region\n");
    fprintf(stderr, "    [-testBG[Region]     tstBGMin            (-3        ).as(Real                ) \n                         tstBGMax            (3         ).as(Real                ) \n                         tstBGDelta          (0.1       ).as(Real                ) ] :Optional  :SearchRegion\n");
    fprintf(stderr, "    [-M[ode]             fitMode             (0         ).as(Integer             ) ] :Optional  :DensityFittngMethod: Mode\n");
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
