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
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-h[alf]v[aluepoint]l[ow]hvl                 (1.0       ).as(Real                ) ] :Optional  :HalfValuePointLow\n");
    fprintf(stderr, "    [-h[alf]v[aluepoint]h[igh]hvh                 (1.0       ).as(Real                ) ] :Optional  :HalfValuePointHigh\n");
    fprintf(stderr, "    [-w[idth]l[ow]       wl                  (1.0       ).as(Real                ) ] :Optional  :WidthOfDumpingLow\n");
    fprintf(stderr, "    [-w[idth]h[igh]      wh                  (1.0       ).as(Real                ) ] :Optional  :WidthOfDumpingHigh\n");
    fprintf(stderr, "    [-lowweight          lowWeight           (0.0       ).as(Real                ) ] :Optional  :Weight of Low Freq.\n");
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
