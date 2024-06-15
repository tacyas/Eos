#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i1[nput]           In1                 (NULL      ).as(inFile              ) ] :Optional  :In: NearSide\n");
    fprintf(stderr, "    [-i2[nput]           In2                 (NULL      ).as(inFile              ) ] :Optional  :In: FarSide\n");
    fprintf(stderr, "    [-o1[utput]          Out1                (NULL      ).as(outFile             ) ] :Optional  :Out: NearSide\n");
    fprintf(stderr, "    [-o2[utput]          Out2                (NULL      ).as(outFile             ) ] :Optional  :Out: FarSide\n");
    fprintf(stderr, "    [-a[verage]          Avg                 (NULL      ).as(outFile             ) ] :Optional  :Out: Average\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Optional  :Out: FitParam\n");
    fprintf(stderr, "    [-op2[utput]         OutP2               (NULL      ).as(outFile             ) ] :Optional  :OutParam2: FitParam Distribution [mrcImage]\n");
    fprintf(stderr, "    [-t[ruePitch]        truePitch           (0.0       ).as(Real                ) ] :Optional  :TruePitch[A]\n");
    fprintf(stderr, "    [-l[ayer]            L                   (NULL      ).as(inFile              ) ] :Optional  :LayerInfo\n");
    fprintf(stderr, "    [-O[mega]            Omin                (0.0       ).as(Real                ) \n                         Omax                (0.0       ).as(Real                ) \n                         Odelta              (1.0       ).as(Real                ) ] :Optional  :Omega[degree]\n");
    fprintf(stderr, "    [-x[shift]           xmin                (-10.0     ).as(Real                ) \n                         xmax                (10.0      ).as(Real                ) \n                         xdelta              (0.1       ).as(Real                ) ] :Optional  :shiftx[A]\n");
    fprintf(stderr, "    [-R                  R                   (10.0      ).as(Real                ) ] :Optional  :Resolution[A]\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
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
