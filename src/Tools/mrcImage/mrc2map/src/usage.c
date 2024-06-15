#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-noswap                                                                       ] :Optional  : NO Byte Swapping \n");
    fprintf(stderr, "    [-shiftx             shiftx              (0.0       ).as(Real                ) ] :Optional  :shiftx\n");
    fprintf(stderr, "    [-shifty             shifty              (0.0       ).as(Real                ) ] :Optional  :shifty\n");
    fprintf(stderr, "    [-shiftz             shiftz              (0.0       ).as(Real                ) ] :Optional  :shiftz\n");
    fprintf(stderr, "    [-mul                mul                 (1.0       ).as(Real                ) ] :Optional  :mrc*mul\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode: \n\t\t0 : Same as mrc\n\t\t1 : Helix(CentreIsOrigin)\n\t\t2: BottomRight is Origin\n\t\t3:Box Centre is a origin\n");
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
