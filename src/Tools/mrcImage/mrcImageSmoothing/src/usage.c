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
    fprintf(stderr, "    [-sx                 sx                  (3         ).as(Real                ) ] :Optional  :x of Kernel Size\n");
    fprintf(stderr, "    [-sy                 sy                  (3         ).as(Real                ) ] :Optional  :y of Kernel Size\n");
    fprintf(stderr, "    [-sz                 sz                  (3         ).as(Real                ) ] :Optional  :z of Kernel Size\n");
    fprintf(stderr, "    [-r                  r                   (1         ).as(Real                ) ] :Optional  :Radius of Kernel Size\n");
    fprintf(stderr, "    [-sigma              sigma               (2.0       ).as(Real                ) ] :Optional  :Sigma for Lee-Sigma\n");
    fprintf(stderr, "    [-times              times               (1         ).as(Integer             ) ] :Optional  :Repeat time\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-M[ode2]            mode2               (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-verbose                                                                      ] :Optional  :Verbose\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
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
