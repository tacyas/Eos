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
    fprintf(stderr, "    [-s[ize]             sizeX               (1         ).as(Integer             ) \n                         sizeY               (1         ).as(Integer             ) ] :Optional  :Mask Size (Odd Only) /pixel\n");
    fprintf(stderr, "    [-v[ector]1          v1x                 (1         ).as(Real                ) \n                         v1y                 (0         ).as(Real                ) ] :Essential :Vector1(/A):x y\n");
    fprintf(stderr, "    [-v[ector]2          v2x                 (0         ).as(Real                ) \n                         v2y                 (1         ).as(Real                ) ] :Optional  :Vector2(/A):x y\n");
    fprintf(stderr, "    [-in[initial number] inum                (1         ).as(Integer             ) ] :Optional  :Initialn number of data to cut out.For 1D only.\n");
    fprintf(stderr, "    [-fn[final number]   num                 (0         ).as(Integer             ) ] :Optional  :Final number of data to cut out.For 1D only.Default:All.\n");
    fprintf(stderr, "    [-en[extra number]   exnum               (0         ).as(Integer             ) ] :Optional  :Extra number of data to cut out.For mode 2 only\n");
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
