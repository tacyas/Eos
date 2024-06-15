#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (stdin     ).as(inFile::ASCII       ) ] :Optional  :Input: eosPoint\n");
    fprintf(stderr, "    [-i[nput]t[ype]      InType              (3         ).as(Integer             ) ] :Optional  :Input: eosPointType\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile::ASCII      ) ] :Optional  :Output: eosPoint\n");
    fprintf(stderr, "    [-o[utput]t[ype]     OutType             (3         ).as(Integer             ) ] :Optional  :Input: eosPointType\n");
    fprintf(stderr, "    [-E[uler]A[ngle]     EAMode              (YOYS      ).as(String              ) \n                         Rot1                (0.0       ).as(Real                ) \n                         Rot2                (0.0       ).as(Real                ) \n                         Rot3                (0.0       ).as(Real                ) ] :Optional  :Input: EulerAngleMode Rot1 Rot2 Rot3\n");
    fprintf(stderr, "    [-I[nput]            InList              (NULL      ).as(inFileList::ASCII   ) ] :Optional  :Input:  eosPointFileList\n");
    fprintf(stderr, "    [-O[uput]            OutList             (NULL      ).as(outFileList::ASCII  ) ] :Optional  :Output: eosPointFileList\n");
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
