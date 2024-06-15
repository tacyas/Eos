#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-I[nput]            InList              (NULL      ).as(inFileList          ) ] :Essential :Input:ImageFileList\n");
    fprintf(stderr, "    [-o[utput]1d         Out1D               (NULL      ).as(outFile             ) ] :Optional  :Output:\n");
    fprintf(stderr, "    [-o[utput]1de[nlarged]Out1DEnlarged       (NULL      ).as(outFile             ) ] :Optional  :Output:\n");
    fprintf(stderr, "    [-o[utput]2d         Out2D               (NULL      ).as(outFile             ) ] :Optional  :Output:\n");
    fprintf(stderr, "    [-a[xis]P[osition]   OriginX             (0.0       ).as(Real                ) \n                         OriginY             (0.0       ).as(Real                ) \n                         OriginZ             (0.0       ).as(Real                ) ] :Optional  :Input: AxisPosition\n");
    fprintf(stderr, "    [-a[xisAngle]        AxisAngleYaw        (0.0       ).as(Real                ) \n                         AxisAnglePitch      (0.0       ).as(Real                ) ] :Optional  :Input: AxisAngleYaw/Pitch[degree]\n");
    fprintf(stderr, "    [-R                  Rmin                (0.05      ).as(Real                ) \n                         Rmax                (0.1       ).as(Real                ) ] :Optional  :Input: LowPathFiltering\n");
    fprintf(stderr, "    [-Interp[olationMode]InterpolationMode   (2         ).as(Integer             ) ] :Optional  :Input: InterpolationMode\n");
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
