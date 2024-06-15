#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            inFile              (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           outFile             (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-H[igh]             High                (0         ).as(Real                ) ] :Optional  :HighThreshold\n");
    fprintf(stderr, "    [-L[ow]              Low                 (0         ).as(Real                ) ] :Optional  :LowThreshold\n");
    fprintf(stderr, "    [-I[nverse]                                                                    ] :Optional  :Inverse(Black is white)\n");
    fprintf(stderr, "    [-z[Section]         Z                   (0         ).as(Integer             ) ] :Optional  :z-section\n");
    fprintf(stderr, "    [-e[xtention]        format              (%%s.%%04d ).as(String              ) ] :Optional  :SerialSection Format\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode: \n\t\t\t0 (8bits), 1(16bits)\n\t\t\t\n");
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
