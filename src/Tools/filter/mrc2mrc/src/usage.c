#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: \n");
    fprintf(stderr, "    [-i[nput]t[ype]      InType              (FEIextendedMRC).as(String              ) ] :Optional  :InputDataType\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-o[utput]t[ype]     OutType             (Eos       ).as(String              ) ] :Optional  :OutputDataType\n");
    fprintf(stderr, "    [-Length             LenX                (1.0       ).as(Real                ) \n                         LenY                (1.0       ).as(Real                ) \n                         LenZ                (1.0       ).as(Real                ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-M                  Mx                  (1         ).as(Integer             ) \n                         My                  (1         ).as(Integer             ) \n                         Mz                  (1         ).as(Integer             ) ] :Optional  :M\n");
    fprintf(stderr, "    [-flagStat                                                                     ] :Optional  :Statistics again\n");
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
