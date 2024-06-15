#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (stdin     ).as(inFile              ) ] :Essential :InputFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-kV                 kV                  (200       ).as(Real                ) ] :Optional  :AccVol[kV]\n");
    fprintf(stderr, "    [-Cs                 Cs                  (1.7       ).as(Real                ) ] :Optional  :Cs[mm]\n");
    fprintf(stderr, "    [-df                 Defocus             (2.7       ).as(Real                ) ] :Essential :Defocus[A]:under(+)\n");
    fprintf(stderr, "    [-n1                 deg1                (2         ).as(Integer             ) ] :Optional  :Degree of zero point minimum\n");
    fprintf(stderr, "    [-n2                 deg2                (4         ).as(Integer             ) ] :Optional  :Degree of zero point maximum\n");
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
