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
    fprintf(stderr, "    [-stereo             Stereo              (6.0       ).as(Real                ) ] :Optional  :Stereo View [degree] around z-axis\n");
    fprintf(stderr, "    [-rotation           nRotation           (60        ).as(Integer             ) \n                         RotationAngle       (6.0       ).as(Real                ) ] :Optional  :(Number, angle) : Rotation View around z-axis\n");
    fprintf(stderr, "    [-eye[Position]      eyeX                (100.0     ).as(Real                ) \n                         eyeY                (0.0       ).as(Real                ) \n                         eyeZ                (0.0       ).as(Real                ) ] :Optional  :Eye Position\n");
    fprintf(stderr, "    [-plane[Position]    planeX              (0.0       ).as(Real                ) \n                         planeY              (0.0       ).as(Real                ) \n                         planeZ              (0.0       ).as(Real                ) ] :Optional  :Plane Position\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-C[ontour]          contourLevel        (0.0       ).as(Real                ) ... ] :Variable  :Contour Level ...\n");
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
