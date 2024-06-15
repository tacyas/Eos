#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input: mrc(3D)\n");
    fprintf(stderr, "    [-t[emplate]         Template            (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input: mrcFFT(2D)\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile::mrcImage   ) ] :Essential :Output: mrcFFT(2D)\n");
    fprintf(stderr, "    [-o[utput]I[mage]    OutImage            (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output: mrcImage(2D)\n");
    fprintf(stderr, "    [-E[uler]A[ngle]     EAMode              (YOYS      ).as(String              ) \n                         Rot1                (0.0       ).as(Real                ) \n                         Rot2                (0.0       ).as(Real                ) \n                         Rot3                (0.0       ).as(Real                ) ] :Optional  :EulerAngle\n");
    fprintf(stderr, "    [-trans[late]        TransX              (0.0       ).as(Real                ) \n                         TransY              (0.0       ).as(Real                ) ] :Optional  :Traslation(2D)\n");
    fprintf(stderr, "    [-InterpMode         InterpMode          (0         ).as(Integer             ) ] :Optional  :Interpolation Mode\n");
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
