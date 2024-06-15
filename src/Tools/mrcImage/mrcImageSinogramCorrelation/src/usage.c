#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: in[sinogram: mrc]\n");
    fprintf(stderr, "    [-r[ef]              Ref                 (NULL      ).as(inFile              ) ] :Essential :Input: ref[sinogram: mrc]\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-w[eigth]           w0th                (1.0       ).as(Real                ) \n                         w1st                (0.0       ).as(Real                ) \n                         w2nd                (0.0       ).as(Real                ) ] :Optional  :Weigth for Mode: 1\n");
    fprintf(stderr, "    [-T[hreshold]        threshold           (0.0       ).as(Real                ) ] :Optional  :threshold for Mode: 2\n");
    fprintf(stderr, "    [-M[odeforCorrelation]corMode             (0         ).as(Integer             ) ] :Optional  :Mode: for Correlation\n");
    fprintf(stderr, "    [-L[ength]M[ode]     LengthMode          (0         ).as(Integer             ) ] :Optional  :Length Mode: for LengthCorrelation\n");
    fprintf(stderr, "    [-L[ength]T[hreshold]M[ode]LengthThresholdMode (0         ).as(Integer             ) ] :Optional  :Length Threshold Mode: for LengthCorrelation\n");
    fprintf(stderr, "    [-L[ength]T[hreshold]R[atio]LengthThresholdRatio(1.0       ).as(Real                ) ] :Optional  :ratio of threshold for LenthMode: 1\n");
    fprintf(stderr, "    [-L[ength]C[orrelation]M[ode]LCMode              (0         ).as(Integer             ) ] :Optional  :Mode: for LengthCorrelationMode\n");
    fprintf(stderr, "    [-L[ength]C[orrelation]T[hreshold]LengthCorrelationThreshold(0.0       ).as(Real                ) ] :Optional  :threshold for LengthCorrelation\n");
    fprintf(stderr, "    [-w[eight]L[ength]   weightLength        (1.0       ).as(Real                ) ] :Optional  :Weight for LengthCorrelation\n");
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
