#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: pdbFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output: Coordinates List\n");
    fprintf(stderr, "    [-P[ointOfInterest]  Px                  (0.0       ).as(Real                ) \n                         Py                  (0.0       ).as(Real                ) \n                         Pz                  (0.0       ).as(Real                ) ] :Optional  :PointOfInterest: Coordinates \n");
    fprintf(stderr, "    [-V[olumeOfInterest] MRC                 (NULL      ).as(inFile              ) ] :Optional  :VolumeOfInterest: MRC\n");
    fprintf(stderr, "    [-C[outourLevel]     Contour             (0.0       ).as(Real                ) ] :Optional  :ContourLevel for VolumeOfInterest: MRC\n");
    fprintf(stderr, "    [-d[istance]         distance            (0.0       ).as(Real                ) ] :Optional  :Distance [A]\n");
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
