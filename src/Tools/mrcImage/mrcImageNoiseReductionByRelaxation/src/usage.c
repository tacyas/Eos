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
    fprintf(stderr, "    [-n[umber]           Nlab                (8         ).as(Integer             ) ] :Optional  :Number of Density Level\n");
    fprintf(stderr, "    [-max[imum]          max                 (0         ).as(Integer             ) ] :Optional  :Maximum of Density Level\n");
    fprintf(stderr, "    [-min[imum]          min                 (0         ).as(Integer             ) ] :Optional  :Minimum of Density Level\n");
    fprintf(stderr, "    [-m[ode]1            mode1               (1         ).as(Integer             ) ] :Optional  :Dij Modeof Personal Style\n");
    fprintf(stderr, "    [-m[ode]2            mode2               (1         ).as(Integer             ) ] :Optional  :Dij Mode of Figure Style\n");
    fprintf(stderr, "    [-m[ode]3            mode3               (1         ).as(Integer             ) ] :Optional  :Dij Mode of Dimension Style\n");
    fprintf(stderr, "    [-o[ptional]m[ode]   omode               (0         ).as(Integer             ) ] :Optional  :Optional Mode of Noise Reduction\n");
    fprintf(stderr, "    [-t[imes]            times               (1         ).as(Integer             ) ] :Optional  :Times of NoiseReduction\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :mode\n");
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
