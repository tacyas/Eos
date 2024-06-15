#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFileList::ASCII   ) ] :Essential :Input: \n");
    fprintf(stderr, "    [-i[nput]t[ype]      InType              (2         ).as(Integer             ) ] :Optional  :Input: \n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFileList::ASCII  ) ] :Essential :Output: \n");
    fprintf(stderr, "    [-o[utput]t[ype]     OutType             (2         ).as(Integer             ) ] :Optional  :Input: \n");
    fprintf(stderr, "    [-o[utput]EA         OutEA               (NULL      ).as(outFileList::ASCII  ) ] :Essential :Output: \n");
    fprintf(stderr, "    [-zero               ZeroPlane           (0         ).as(Integer             ) ] :Optional  :Zero Plane\n");
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