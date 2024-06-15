#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile (Template file)\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-C[enter]           Cx                  (0         ).as(Real                ) \n                         Cy                  (0         ).as(Real                ) \n                         Cz                  (0         ).as(Real                ) ] :Optional  :Cetnter position of Sphere.\n");
    fprintf(stderr, "    [-or[Outer Radius]   or                  (1         ).as(Real                ) ] :Essential :Outer Radius (pixel)\n");
    fprintf(stderr, "    [-ir[Inner Radius]   ir                  (0         ).as(Real                ) ] :Optional  :Inner Radius (pixel)\n");
    fprintf(stderr, "    [-r[adius]           r                   (0         ).as(Real                ) ] :Optional  :Center Radius (pixel): For mode 1 only.\n");
    fprintf(stderr, "    [-v[alue]            Value               (10.0      ).as(Real                ) ] :Optional  :Value of sphere\n");
    fprintf(stderr, "    [-Other              Other               (NULL      ).as(inFile              ) ] :Optional  :Other acceptors.  For FRET Calculation.\n");
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
