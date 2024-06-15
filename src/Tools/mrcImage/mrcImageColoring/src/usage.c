#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-r[ed]              rIn                 (NULL      ).as(inFile              ) ] :Optional  :Red:InputDataFile\n");
    fprintf(stderr, "    [-g[reen]            gIn                 (NULL      ).as(inFile              ) ] :Optional  :Green:InputDataFile\n");
    fprintf(stderr, "    [-b[lue]             bIn                 (NULL      ).as(inFile              ) ] :Optional  :Blue:InputDataFile\n");
    fprintf(stderr, "    [-rH[ight]           rHigh               (1         ).as(Real                ) ] :Optional  :Red:HighThres\n");
    fprintf(stderr, "    [-rL[ow]             rLow                (0         ).as(Real                ) ] :Optional  :Red:LowThres\n");
    fprintf(stderr, "    [-gH[ight]           gHigh               (1         ).as(Real                ) ] :Optional  :Green:HighThres\n");
    fprintf(stderr, "    [-gL[ow]             gLow                (0         ).as(Real                ) ] :Optional  :Green:LowThres\n");
    fprintf(stderr, "    [-bH[ibht]           bHigh               (1         ).as(Real                ) ] :Optional  :Blue:HibhThres\n");
    fprintf(stderr, "    [-bL[ow]             bLow                (0         ).as(Real                ) ] :Optional  :BLue:LowThres\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Optional  :gif:OutputDataFile\n");
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
