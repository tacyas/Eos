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
    fprintf(stderr, "    [-dang               dang                (10        ).as(Real                ) ] :Optional  :Delta Angle[degree]\n");
    fprintf(stderr, "    [-zmin               zmin                (0         ).as(Real                ) ] :Optional  :Z Minimum[A]\n");
    fprintf(stderr, "    [-zmax               zmax                (100       ).as(Real                ) ] :Optional  :Z Maximum[A]\n");
    fprintf(stderr, "    [-dz                 dz                  (10        ).as(Real                ) ] :Optional  :Delta Z[A]\n");
    fprintf(stderr, "    [-rmin               rmin                (0         ).as(Real                ) ] :Optional  :Radius Minimum[A]\n");
    fprintf(stderr, "    [-rmax               rmax                (200       ).as(Real                ) ] :Optional  :Radius Maximum[A]\n");
    fprintf(stderr, "    [-threshold          threshold           (0         ).as(Real                ) ] :Optional  :Set threshold value.  Averaged density is more than threshold value\n");
    fprintf(stderr, "    [-dr                 dr                  (10        ).as(Real                ) ] :Optional  :Delta Radius[A]\n");
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
