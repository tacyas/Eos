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
    fprintf(stderr, "    [-r[oi]              roiLine             (NULL      ).as(Real                ) ... ] :Variable  :\n");
    fprintf(stderr, "    [-x                  x                   (1.0       ).as(Real                ) ] :Essential :Width :Source \n");
    fprintf(stderr, "    [-y                  y                   (1.0       ).as(Real                ) ] :Optional  :Height:Source\n");
    fprintf(stderr, "    [-W                  Width               (1.0       ).as(Real                ) ] :Optional  :Width :Dst \n");
    fprintf(stderr, "    [-H                  Height              (1.0       ).as(Real                ) ] :Optional  :Height:Dst \n");
    fprintf(stderr, "    [-cor                Cor                 (360.0     ).as(Real                ) ] :Optional  :Correlation Window along Y-axis [A]\n");
    fprintf(stderr, "    [-S[hrink]           Shrink              (1         ).as(Integer             ) ] :Optional  :When inputfile is shrinked:\n");
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
