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
    fprintf(stderr, "    [-x                  X                   (0.0       ).as(Real                ) ] :Optional  :Move X[A]\n");
    fprintf(stderr, "    [-y                  Y                   (0.0       ).as(Real                ) ] :Optional  :Move Y[A]\n");
    fprintf(stderr, "    [-z                  Z                   (0.0       ).as(Real                ) ] :Optional  :Move Z[A]\n");
    fprintf(stderr, "    [-originTo           toX                 (0.0       ).as(Real                ) \n                         toY                 (0.0       ).as(Real                ) \n                         toZ                 (0.0       ).as(Real                ) ] :Optional  :move (0,0,0) to (X,Y,Z)\n");
    fprintf(stderr, "    [-toOrigin           fromX               (0.0       ).as(Real                ) \n                         fromY               (0.0       ).as(Real                ) \n                         fromZ               (0.0       ).as(Real                ) ] :Optional  :move (X,Y,Z) to (0,0,0)\n");
    fprintf(stderr, "    [-GCtoOrigin                                                                   ] :Optional  :GC(Gravity Centre) to origin\n");
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
