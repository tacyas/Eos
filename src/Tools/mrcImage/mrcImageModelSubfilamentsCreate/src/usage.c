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
    fprintf(stderr, "    [-nx                 nx                  (71        ).as(Integer             ) ] :Optional  :Real length = nx * lx\n");
    fprintf(stderr, "    [-ny                 ny                  (71        ).as(Integer             ) ] :Optional  :Real length = ny * ly\n");
    fprintf(stderr, "    [-nz                 nz                  (100       ).as(Integer             ) ] :Optional  :Real lenght = nz * lz\n");
    fprintf(stderr, "    [-lx                 lx                  (5.0       ).as(Real                ) ] :Optional  :Pixel Size[Angstrom]\n");
    fprintf(stderr, "    [-ly                 ly                  (5.0       ).as(Real                ) ] :Optional  :Pixel Size[Angstrom]\n");
    fprintf(stderr, "    [-lz                 lz                  (5.0       ).as(Real                ) ] :Optional  :Pixel Size[Angstrom]\n");
    fprintf(stderr, "    [-position           position            (70        ).as(Real                ) ] :Optional  :subfilaments position from center [A]\n");
    fprintf(stderr, "    [-n                  nHelix              (3         ).as(Integer             ) ] :Optional  :n-helix\n");
    fprintf(stderr, "    [-dphi               deltaPhi            (1.395348837).as(Real                ) ] :Optional  :rotation angle [degree]\n");
    fprintf(stderr, "    [-sphi               startPhi            (0         ).as(Real                ) ] :Optional  :start angle [degree]\n");
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
