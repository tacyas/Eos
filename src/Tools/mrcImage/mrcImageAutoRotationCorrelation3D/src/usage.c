#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: mrc[test]\n");
    fprintf(stderr, "    [-r[ef]              Ref                 (NULL      ).as(inFile              ) ] :Essential :Input: mrc[ref]\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output: Parameter\n");
    fprintf(stderr, "    [-cor                Cor                 (NULL      ).as(outFile             ) ] :Optional  :Output: CorMap\n");
    fprintf(stderr, "    [-fit                Fit                 (stdout    ).as(outFile             ) ] :Optional  :Output: Best Fit\n");
    fprintf(stderr, "    [-E[uler]A[ngle]     EulerAngle          (YOYS      ).as(String              ) ] :Optional  :Input: EulerAngle\n");
    fprintf(stderr, "    [-Rot1               Rot1Min             (0.0       ).as(Real                ) \n                         Rot1Max             (360.0     ).as(Real                ) \n                         Rot1Delta           (5.0       ).as(Real                ) ] :Optional  :Rot1\n");
    fprintf(stderr, "    [-Rot2               Rot2Min             (0.0       ).as(Real                ) \n                         Rot2Max             (180.0     ).as(Real                ) \n                         Rot2Delta           (5.0       ).as(Real                ) ] :Optional  :Rot2\n");
    fprintf(stderr, "    [-Rot3               Rot3Min             (0.0       ).as(Real                ) \n                         Rot3Max             (360.0     ).as(Real                ) \n                         Rot3Delta           (5.0       ).as(Real                ) ] :Optional  :Rot3\n");
    fprintf(stderr, "    [-Xrange             XrangeMin           (0         ).as(Real                ) \n                         XrangeMax           (0         ).as(Real                ) ] :Optional  :Xrange[pixel]: Not set, all space search\n");
    fprintf(stderr, "    [-Yrange             YrangeMin           (0         ).as(Real                ) \n                         YrangeMax           (0         ).as(Real                ) ] :Optional  :Yrange[pixel]: Not set, all space search\n");
    fprintf(stderr, "    [-Zrange             ZrangeMin           (0         ).as(Real                ) \n                         ZrangeMax           (0         ).as(Real                ) ] :Optional  :Zrange[pixel]: Not set, all space search\n");
    fprintf(stderr, "    [-M[ode]             Mode                (0         ).as(Integer             ) ] :Optional  :Mode: Correlation Mode\n");
    fprintf(stderr, "    [-M[ode]R[otation]   ModeRotation        (0         ).as(Integer             ) ] :Optional  :Mode: Rotation3D Mode\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode: InterpolationMode\n");
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
