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
    fprintf(stderr, "    [-d[ensity]          Density             (55.55555  ).as(Real                ) ] :Optional  :[M]: Density of Water\n");
    fprintf(stderr, "    [-r[adius]           Radius              (100.      ).as(Real                ) ] :Optional  :[A]: Radius of Water Volume: Sphere, Cylinder\n");
    fprintf(stderr, "    [-height             Height              (100.      ).as(Real                ) ] :Optional  :[A]: Height of Water Volume : Cylinder\n");
    fprintf(stderr, "    [-cube               X                   (100.      ).as(Real                ) \n                         Y                   (100.      ).as(Real                ) \n                         Z                   (100.      ).as(Real                ) ] :Optional  :[A]: Cube\n");
    fprintf(stderr, "    [-edge               Edge                (3.        ).as(Integer             ) ] :Optional  :layer number: Edge\n");
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
