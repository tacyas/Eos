#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]2           In2x                (NULL      ).as(inFile::mrcImage    ) \n                         In2y                (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input\n");
    fprintf(stderr, "    [-i[nput]3           In3x                (NULL      ).as(inFile::mrcImage    ) \n                         In3y                (NULL      ).as(inFile::mrcImage    ) \n                         In3z                (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile::mrcImage   ) ] :Essential :Output::MagOfCur3D or CurOf2D\n");
    fprintf(stderr, "    [-o[utput]3          Out3x               (NULL      ).as(outFile::mrcImage   ) \n                         Out3y               (NULL      ).as(outFile::mrcImage   ) \n                         Out3z               (NULL      ).as(outFile::mrcImage   ) ] :Optional  :OutputDataFile\n");
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
