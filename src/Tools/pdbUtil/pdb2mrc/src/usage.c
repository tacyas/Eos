#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile(3D)\n");
    fprintf(stderr, "    [-nx                 nx                  (1         ).as(Integer             ) ] :Optional  :Pixel[Def:]\n");
    fprintf(stderr, "    [-ny                 ny                  (1         ).as(Integer             ) ] :Optional  :Pixel[Def:]\n");
    fprintf(stderr, "    [-nz                 nz                  (1         ).as(Integer             ) ] :Optional  :Pixel[Def:]\n");
    fprintf(stderr, "    [-Sx[tart]           Startx              (0.0       ).as(Real                ) ] :Optional  :Startx[A]\n");
    fprintf(stderr, "    [-Sy[tart]           Starty              (0.0       ).as(Real                ) ] :Optional  :Starty[A]\n");
    fprintf(stderr, "    [-Sz[tart]           Startz              (0.0       ).as(Real                ) ] :Optional  :Startz[A]\n");
    fprintf(stderr, "    [-dx                 dx                  (2.5       ).as(Real                ) ] :Optional  :dx\n");
    fprintf(stderr, "    [-dy                 dy                  (2.5       ).as(Real                ) ] :Optional  :dy\n");
    fprintf(stderr, "    [-dz                 dz                  (2.5       ).as(Real                ) ] :Optional  :dz\n");
    fprintf(stderr, "    [-w[eight]           Weight              (1.0       ).as(Real                ) ] :Optional  :Weight\n");
    fprintf(stderr, "    [-sig[ma]            Sigma               (0.0       ).as(Real                ) ] :Optional  :Sigma[A]\n");
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
