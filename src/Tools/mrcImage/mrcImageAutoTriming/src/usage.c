#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input:mrcImage\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile::mrcImage   ) ] :Essential :Output:mrcImage\n");
    fprintf(stderr, "    [-O[utput]           OutParam            (stdout    ).as(outFile::YAML       ) ] :Optional  :OutputParams:YAML\n");
    fprintf(stderr, "    [-E[uler]A[ngle]Mode EAMode              (ZONS      ).as(String              ) ] :Optional  :EulerAngle\n");
    fprintf(stderr, "    [-Rot[ation]1        Rot1Min             (-5        ).as(Real                ) \n                         Rot1Max             (5         ).as(Real                ) \n                         Rot1Delta           (1         ).as(Real                ) ] :Optional  :Rot1\n");
    fprintf(stderr, "    [-Rot[ation]2        Rot2Min             (-5        ).as(Real                ) \n                         Rot2Max             (5         ).as(Real                ) \n                         Rot2Delta           (1         ).as(Real                ) ] :Optional  :Rot2\n");
    fprintf(stderr, "    [-Rot[ation]3        Rot3Min             (-5        ).as(Real                ) \n                         Rot3Max             (5         ).as(Real                ) \n                         Rot3Delta           (1         ).as(Real                ) ] :Optional  :Rot3\n");
    fprintf(stderr, "    [-M[ode]             InterpolationMode   (0         ).as(Integer             ) ] :Optional  :Iterpolation Mode\n");
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
