#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputFETDataFileList\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputEulerAngleDataFileList\n");
    fprintf(stderr, "    [-i[nput]Ref         InR                 (NULL      ).as(inFile              ) ] :Essential :InputReferenceFETDataFileList\n");
    fprintf(stderr, "    [-i[nput]Euler       InE                 (NULL      ).as(inFile              ) ] :Essential :InputEulerAngleDataFile\n");
    fprintf(stderr, "    [-n[ormalize]m[ode]  NM                  (0         ).as(Integer             ) ] :Optional  :normalizeMode\n");
    fprintf(stderr, "    [-o[utputList]m[ode] OM                  (2         ).as(Integer             ) ] :Optional  :outputListMode\n");
    fprintf(stderr, "    [-t[op]n[um]         TN                  (10        ).as(Integer             ) ] :Optional  :top number\n");
    fprintf(stderr, "    [-refR[ange]         RR                  (15        ).as(Integer             ) ] :Optional  :reference select Range\n");
    fprintf(stderr, "    [-w[eight]           WEIGHT              (NULL      ).as(inFile              ) ] :Optional  :CorrelationCalcWeight\n");
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
