#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]1           In1                 (NULL      ).as(inFile::mrcImage    ) ] :Essential :Past\n");
    fprintf(stderr, "    [-i[nput]2           In2                 (NULL      ).as(inFile::mrcImage    ) ] :Essential :Present\n");
    fprintf(stderr, "    [-i[nput]3           In3                 (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Future\n");
    fprintf(stderr, "    [-v[elocity]3        Vx                  (NULL      ).as(inFile::mrcImage    ) \n                         Vy                  (NULL      ).as(inFile::mrcImage    ) \n                         Vz                  (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Velocity\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-E[nlarge]          Enlarge             (1         ).as(Real                ) ] :Optional  :Enlarge\n");
    fprintf(stderr, "    [-o[utput]A          OutAVG              (NULL      ).as(outFile::mrcImage   ) ] :Optional  :OutputDataFile\n");
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
