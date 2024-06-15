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
    fprintf(stderr, "    [-A                  A                   (1.0       ).as(Real                ) ] :Optional  :A\n");
    fprintf(stderr, "    [-B                  B                   (0.0       ).as(Real                ) ] :Optional  :B\n");
    fprintf(stderr, "    [-ContourMin         ContourMin          (0.0       ).as(Real                ) ] :Optional  :ContourMin: density value\n");
    fprintf(stderr, "    [-ContourMax         ContourMax          (10.0      ).as(Real                ) ] :Optional  :ContourMax: density value\n");
    fprintf(stderr, "    [-ContourSolvent     ContourSolvent      (0.0       ).as(Real                ) ] :Optional  :ContourSolvent\n");
    fprintf(stderr, "    [-Low[ValueArea]     thresOfLowValueArea (0.1       ).as(Real                ) ] :Optional  :LowValueArea: rate\n");
    fprintf(stderr, "    [-High[ValueArea]    thresOfHighValueArea(0.9       ).as(Real                ) ] :Optional  :HighValueArea: rate\n");
    fprintf(stderr, "    [-param[eter]o[utput]ParamOut            (stdout    ).as(outFile             ) ] :Optional  :ConfigurationFile\n");
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
