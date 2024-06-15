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
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-r[max]             r                   (0         ).as(Real                ) ] :Optional  :Threshold radius of signal.Default is Nx.\n");
    fprintf(stderr, "    [-w[idth]            w                   (1         ).as(Real                ) ] :Optional  :Width of slope. For mode 1.\n");
    fprintf(stderr, "    [-v[alue]            v                   (0         ).as(Real                ) ] :Optional  :Value of out of threshold.\n");
    fprintf(stderr, "    [-Nx                 Nx                  (0         ).as(Integer             ) ] :Optional  :Number of x.Default is inputfile.\n");
    fprintf(stderr, "    [-Ny                 Ny                  (0         ).as(Integer             ) ] :Optional  :Number of y.Default is inputfile.\n");
    fprintf(stderr, "    [-Nz                 Nz                  (0         ).as(Integer             ) ] :Optional  :Number of z.Default is inputfile.\n");
    fprintf(stderr, "    [-Floating                                                                     ] :Optional  :Floating\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-M[ode2]            mode2               (0         ).as(Integer             ) ] :Optional  :Mode\n");
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
