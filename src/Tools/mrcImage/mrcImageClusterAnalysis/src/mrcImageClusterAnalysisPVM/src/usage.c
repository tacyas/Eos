#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-I[nput array of file]In                  (stdin     )] :Essential :InputDataFiles\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    )] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-O[utput]           ] :Optional  :Output: averaged images\n");
    fprintf(stderr, "    [-N[umber of clusters]N                   (1         )] :Optional  :Number of clusters\n");
    fprintf(stderr, "    [-Iter[ation]        ] :Optional  :IterationFlag\n");
    fprintf(stderr, "    [-A[uto]R[otation]   AutoRotation        (72        )] :Optional  :AutoRotationFlag\n");
    fprintf(stderr, "    [-A[uto]R[otation]iter[ation]AutoRotationIteration(2         )] :Optional  :AutoRotationIteration\n");
    fprintf(stderr, "    [-A[uto]R[otation]MethodAutoRotationMethod  (0         )] :Optional  :Method for Correlation for Auto Rotation\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      )] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-Mi[rrorimage]      ] :Optional  :Mirror Image is considered -m 2 only\n");
    fprintf(stderr, "    [-M[odeForCorrelation]correlationMode     (0x00      )] :Optional  :Correlation Mode for AutoRotation\n");
    fprintf(stderr, "    [-M[ax]P[rocess]     Maxprocess          (8         )] :Optional  :The maximum process number\n");
    fprintf(stderr, "    [-m[ode]             mode                (2         )] :Optional  :Mode\n");
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
