#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input: mrcImage\n");
    fprintf(stderr, "    [-filter             filterIn            (NULL      ).as(inFile::ASCII       ) ] :Essential :Input: filterFile\n");
    fprintf(stderr, "    [-filterCol[lumn]    colR                (1         ).as(Integer             ) \n                         colW                (2         ).as(Integer             ) ] :Optional  :R W\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile::mrcImage   ) ] :Essential :Output: mrcImage\n");
    fprintf(stderr, "    [-L[owCut]           Low                 (-0.1      ).as(Real                ) ] :Optional  :LowCut: [/A]\n");
    fprintf(stderr, "    [-H[ighCut]          High                (1.0       ).as(Real                ) ] :Optional  :HighCut: [/A]\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile::ASCII       ) ] :Optional  :ConfigurationFile\n");
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
