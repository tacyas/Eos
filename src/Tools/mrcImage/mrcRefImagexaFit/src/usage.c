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
    fprintf(stderr, "    [-ix[initial x]      ix                  (NULL      ).as(Integer             ) ] :Optional  :Initial x(pixel)\n");
    fprintf(stderr, "    [-ia[initial alpha]  ia                  (0         ).as(Real                ) ] :Optional  :Initial alpha(degree)\n");
    fprintf(stderr, "    [-r[eference]        Ref                 (NULL      ).as(inFile              ) ] :Optional  :ReferenceFile\n");
    fprintf(stderr, "    [-dy[deltay]         Dy                  (10        ).as(Integer             ) ] :Optional  :Deltay\n");
    fprintf(stderr, "    [-xrange             xrange              (3         ).as(Integer             ) ] :Optional  :x range to search (pixel)\n");
    fprintf(stderr, "    [-arange             arange              (2         ).as(Integer             ) ] :Optional  :alpha range to search (degree)\n");
    fprintf(stderr, "    [-v[alue]            Value               (1         ).as(Real                ) ] :Optional  :Value of Peak Pixel :for mode2\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-M[ode2]            mode2               (0         ).as(Integer             ) ] :Optional  :Mode2\n");
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
