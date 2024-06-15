#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-nx                 nx                  (1         ).as(Integer             ) ] :Optional  :Number:x-axis(a-axis)\n");
    fprintf(stderr, "    [-ny                 ny                  (1         ).as(Integer             ) ] :Optional  :Number:y-axis(b-axis)\n");
    fprintf(stderr, "    [-nz                 nz                  (1         ).as(Integer             ) ] :Optional  :Number:z-axis(c-axis)\n");
    fprintf(stderr, "    [-start              StartX              (0.0       ).as(Real                ) \n                         StartY              (0.0       ).as(Real                ) \n                         StartZ              (0.0       ).as(Real                ) ] :Optional  :start coord(x, y, z)[Ang]\n");
    fprintf(stderr, "    [-A[-axis]           AX                  (1.0       ).as(Real                ) \n                         AY                  (0.0       ).as(Real                ) \n                         AZ                  (0.0       ).as(Real                ) ] :Optional  :a(x, y, z)[Ang]\n");
    fprintf(stderr, "    [-B[-axis]           BX                  (0.0       ).as(Real                ) \n                         BY                  (1.0       ).as(Real                ) \n                         BZ                  (0.0       ).as(Real                ) ] :Optional  :b(x, y, z)[Ang]\n");
    fprintf(stderr, "    [-C[-axis]           CX                  (0.0       ).as(Real                ) \n                         CY                  (0.0       ).as(Real                ) \n                         CZ                  (1.0       ).as(Real                ) ] :Optional  :c(x, y, z)[Ang]\n");
    fprintf(stderr, "    [-M[ode]             Mode                (0         ).as(Integer             ) ] :Optional  :Mode: PixelHow\n");
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
