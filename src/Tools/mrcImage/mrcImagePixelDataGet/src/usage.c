#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input: mrcImage\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile::ASCII      ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-x                  x                   (0.0       ).as(Real                ) ] :Optional  :Input: x\n");
    fprintf(stderr, "    [-y                  y                   (0.0       ).as(Real                ) ] :Optional  :Input: y\n");
    fprintf(stderr, "    [-z                  z                   (0.0       ).as(Real                ) ] :Optional  :Input: z\n");
    fprintf(stderr, "    [-In[put]            InCoord             (stdin     ).as(inFile::ASCII       ) ] :Optional  :Input:eosPoint\n");
    fprintf(stderr, "    [-cuda               cudaDeviceID        (0         ).as(Integer             ) ] :Optional  :cudaDeviceID\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-o[utput]m[ode]     outMode             (0         ).as(Integer             ) ] :Optional  :Mode:Output\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode:Interpolation\n");
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
