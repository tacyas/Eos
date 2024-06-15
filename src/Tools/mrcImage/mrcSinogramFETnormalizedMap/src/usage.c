#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputFETlistFile\n");
    fprintf(stderr, "    [-o[utput]           OutFET              (NULL      ).as(outFile             ) ] :Essential :OutputFETmrcformat\n");
    fprintf(stderr, "    [-cl[ine]List        comList             (NULL      ).as(inFile              ) ] :Optional  :commonlineList\n");
    fprintf(stderr, "    [-O[utput]           OutMAP              (NULL      ).as(outFile             ) ] :Optional  :OutputMAPmrcformat\n");
    fprintf(stderr, "    [-w[eight]           Weight              (NULL      ).as(inFile              ) ] :Optional  :WeightForDistanceCalc\n");
    fprintf(stderr, "    [-atm[ode]           AAtm                (1         ).as(Integer             ) ] :Optional  :AAtestmode\n");
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
