#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input:mrc\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output:mrc\n");
    fprintf(stderr, "    [-d[elta]p[hi]       delPhi              (30        ).as(Real                ) ] :Optional  :deltaPhi [degree]\n");
    fprintf(stderr, "    [-d[elta]z           delZ                (5.5       ).as(Real                ) ] :Optional  :deltaZ [degree]\n");
    fprintf(stderr, "    [-Nx                 Nx                  (0         ).as(Integer             ) ] :Optional  :[pixel]\n");
    fprintf(stderr, "    [-Ny                 Ny                  (0         ).as(Integer             ) ] :Optional  :[pixel]\n");
    fprintf(stderr, "    [-Nz                 Nz                  (0         ).as(Integer             ) ] :Optional  :[pixel]\n");
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