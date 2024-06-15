#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In2D                (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input: 2D(FFT)\n");
    fprintf(stderr, "    [-i[nput]3d          In3D                (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input: 3D(FFT)\n");
    fprintf(stderr, "    [-E[uler]A[ngle]     EAMode              (YOYS      ).as(String              ) \n                         Rot1                (0.0       ).as(Real                ) \n                         Rot2                (0.0       ).as(Real                ) \n                         Rot3                (0.0       ).as(Real                ) ] :Optional  :Input: EulerAngle\n");
    fprintf(stderr, "    [-trans[late]        TransX              (0.0       ).as(Real                ) \n                         TransY              (0.0       ).as(Real                ) ] :Optional  :Input: Translation\n");
    fprintf(stderr, "    [-InterpMode         InterpMode          (0         ).as(Integer             ) ] :Optional  :Interpolation Mode\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output:Likelihood\n");
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
