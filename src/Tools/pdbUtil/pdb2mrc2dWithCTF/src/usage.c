#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: PDB\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output: MRC\n");
    fprintf(stderr, "    [-N                  Nx                  (2048      ).as(Integer             ) \n                         Ny                  (2048      ).as(Integer             ) ] :Optional  :Input: Nx Ny [pixel]\n");
    fprintf(stderr, "    [-d                  dx                  (1.72      ).as(Real                ) \n                         dy                  (1.72      ).as(Real                ) ] :Optional  :Input: dx dy [A]\n");
    fprintf(stderr, "    [-Centre             cx                  (0         ).as(Real                ) \n                         cy                  (0         ).as(Real                ) \n                         cz                  (0         ).as(Real                ) ] :Optional  :Input: CentreX CentreY [A]\n");
    fprintf(stderr, "    [-n                  nx                  (64        ).as(Integer             ) \n                         ny                  (64        ).as(Integer             ) ] :Optional  :Input: nx ny for subimage [pixel]\n");
    fprintf(stderr, "    [-kV                 kV                  (200.      ).as(Real                ) ] :Optional  :kV \n");
    fprintf(stderr, "    [-Cs                 Cs                  (1.7       ).as(Real                ) ] :Optional  :Cs \n");
    fprintf(stderr, "    [-d[e]f[ocus]        Defocus             (10000     ).as(Real                ) ] :Optional  :Defocus [A] at z = 0\n");
    fprintf(stderr, "    [-A[overP]           AoverP              (0.07      ).as(Real                ) ] :Optional  :AoverP\n");
    fprintf(stderr, "    [-Ain                Ain                 (0.2       ).as(Real                ) ] :Optional  :Beta: IlluminationAngle [mrad]\n");
    fprintf(stderr, "    [-ctfMode            ctfMode             (33        ).as(Integer             ) ] :Optional  :ctfMode\n");
    fprintf(stderr, "    [-E[uler]A[ngle]     EulerAngle          (XEYS      ).as(String              ) \n                         Rot1                (0         ).as(Real                ) \n                         Rot2                (0         ).as(Real                ) \n                         Rot3                (0         ).as(Real                ) ] :Optional  :EulerAngle: [degree]\n");
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
