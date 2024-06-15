#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: MRC(3D)\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output: SymmetryFindParameters\n");
    fprintf(stderr, "    [-a[verage]          Avg                 (NULL      ).as(outFile             ) ] :Optional  :Output: SymmetryAverage\n");
    fprintf(stderr, "    [-S[paceGroupNumber] ISGN                (0         ).as(Integer             ) ] :Optional  :SpaceGroupNumber\n");
    fprintf(stderr, "    [-Rot[ation]Mode     RotMode             (XOYS      ).as(String              ) ] :Optional  :EulerMode\n");
    fprintf(stderr, "    [-Rot1               minRot1             (0.        ).as(Real                ) \n                         maxRot1             (360.      ).as(Real                ) \n                         dRot1               (1.0       ).as(Real                ) ] :Optional  :[degree]\n");
    fprintf(stderr, "    [-Rot2               minRot2             (-90.      ).as(Real                ) \n                         maxRot2             (90.       ).as(Real                ) \n                         dRot2               (1.0       ).as(Real                ) ] :Optional  :[degree]\n");
    fprintf(stderr, "    [-dCos               dCos                (1         ).as(Integer             ) ] :Optional  :dCos\n");
    fprintf(stderr, "    [-CorMode            corMode             (16        ).as(Integer             ) ] :Optional  :CorrelationMode\n");
    fprintf(stderr, "    [-OffsetMode         OffsetMode          (0         ).as(Integer             ) ] :Optional  :OffsetMode\n");
    fprintf(stderr, "    [-InterpolationMode  InterpolationMode   (2         ).as(Integer             ) ] :Optional  :InterpolationMode\n");
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
