#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-nx                 nx                  (70        ).as(Integer             ) ] :Optional  :Real length = nx * lx\n");
    fprintf(stderr, "    [-ny                 ny                  (70        ).as(Integer             ) ] :Optional  :Real length = ny * ly\n");
    fprintf(stderr, "    [-nz                 nz                  (100       ).as(Integer             ) ] :Optional  :Real lenght = nz * lz\n");
    fprintf(stderr, "    [-r                  r                   (1         ).as(Integer             ) ] :Optional  :Radius[pixel]\n");
    fprintf(stderr, "    [-l                  l                   (1         ).as(Integer             ) ] :Optional  :Length[pixel]\n");
    fprintf(stderr, "    [-lx                 lx                  (5.0       ).as(Real                ) ] :Optional  :Pixel Size[Angstrom]\n");
    fprintf(stderr, "    [-ly                 ly                  (5.0       ).as(Real                ) ] :Optional  :Pixel Size[Angstrom]\n");
    fprintf(stderr, "    [-lz                 lz                  (5.0       ).as(Real                ) ] :Optional  :Pixel Size[Angstrom]\n");
    fprintf(stderr, "    [-radius             radius              (150       ).as(Real                ) ] :Optional  :filament radius [A]\n");
    fprintf(stderr, "    [-n                  nHelix              (3         ).as(Integer             ) ] :Optional  :n-helix\n");
    fprintf(stderr, "    [-dz                 zPitch              (143       ).as(Real                ) ] :Optional  :pitch [A]\n");
    fprintf(stderr, "    [-dphi               deltaPhi            (40        ).as(Real                ) ] :Optional  :rotation angle [degree]\n");
    fprintf(stderr, "    [-phi                phiAngle            (120       ).as(Real                ) ] :Optional  :rotation angle in the same level [degree]\n");
    fprintf(stderr, "    [-sz                 startZ              (0         ).as(Real                ) ] :Optional  :start z [A]\n");
    fprintf(stderr, "    [-ez                 endZ                (500       ).as(Real                ) ] :Optional  :end z [A]\n");
    fprintf(stderr, "    [-sphi               startPhi            (0         ).as(Real                ) ] :Optional  :start angle [degree]\n");
    fprintf(stderr, "    [-sphi2              startPhi2           (40        ).as(Real                ) ] :Optional  :start angle 2 [degree]\n");
    fprintf(stderr, "    [-inMode             inMode              (0         ).as(Integer             ) ] :Optional  :inMode\n");
    fprintf(stderr, "    [-units              units               (9         ).as(Integer             ) ] :Optional  :units number\n");
    fprintf(stderr, "    [-fm                 fm                  (0         ).as(Integer             ) ] :Optional  :formation\n");
    fprintf(stderr, "    [-range              min                 (0         ).as(Real                ) \n                         max                 (10        ).as(Real                ) ] :Optional  :value-range\n");
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
