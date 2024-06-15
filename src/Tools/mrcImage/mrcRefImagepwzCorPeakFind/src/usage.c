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
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-N[unber]           N                   (20        ).as(Integer             ) ] :Optional  :Number of peaks\n");
    fprintf(stderr, "    [-dN[delta number]   dN                  (5         ).as(Integer             ) ] :Optional  :Number of template shift\n");
    fprintf(stderr, "    [-d[elta]p[hi]       dp                  (166.1538462).as(Real                ) ] :Optional  :Delta phi(Degree)\n");
    fprintf(stderr, "    [-d[elta]z           dz                  (27.3      ).as(Real                ) ] :Optional  :Delta z(A)\n");
    fprintf(stderr, "    [-l[ength]           length              (1000      ).as(Integer             ) ] :Optional  :Length to extract.:mode 2 only\n");
    fprintf(stderr, "    [-div[ision]         div                 (1         ).as(Integer             ) ] :Optional  :Number to division.:mode 2 only\n");
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
