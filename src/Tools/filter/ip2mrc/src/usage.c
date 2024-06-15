#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile[.img]\n");
    fprintf(stderr, "    [-i2[nput]           InTem               (NULL      ).as(inFile              ) ] :Optional  :InputDataFile[.tem]\n");
    fprintf(stderr, "    [-i3[nput]           InInf               (NULL      ).as(inFile              ) ] :Optional  :InputDataFile[.inf]\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-o2[utput]          Out2                (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile[1/4]\n");
    fprintf(stderr, "    [-Mag                Mag                 (40000     ).as(Real                ) ] :Optional  :Magnification\n");
    fprintf(stderr, "    [-SE                 SE                  (200       ).as(Real                ) ] :Optional  :SE\n");
    fprintf(stderr, "    [-OutMode            OutMode             (1         ).as(Integer             ) ] :Optional  :OutPutMode\n");
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
