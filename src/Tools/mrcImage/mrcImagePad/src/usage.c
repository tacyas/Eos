#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input DataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output DataFile\n");
    fprintf(stderr, "    [-W[idth]            Width               (0         ).as(Integer             ) ] :Optional  :Width[pixel]\n");
    fprintf(stderr, "    [-H[eight]           Height              (0         ).as(Integer             ) ] :Optional  :Height[pixel]\n");
    fprintf(stderr, "    [-V[alue]            Value               (0.0       ).as(Real                ) ] :Optional  :Padding Value(float on avgrage density)\n");
    fprintf(stderr, "    [-E[xpected]V[alue]  ExpectedValue       (0.0       ).as(Real                ) ] :Optional  :Expected Value for Background\n");
    fprintf(stderr, "    [-AW                 AvgWnd              (2000.0    ).as(Real                ) ] :Optional  :Averaging Window Size [A]\n");
    fprintf(stderr, "    [-AWMin              AWMin               (20        ).as(Real                ) ] :Optional  :Averaging Window Size[pixel]\n");
    fprintf(stderr, "    [-AWMax              AWMax               (22        ).as(Real                ) ] :Optional  :Averaging Window Size[pixel]\n");
    fprintf(stderr, "    [-Tilt               TiltAxisAngle       (0         ).as(Real                ) \n                         TiltAngle           (0         ).as(Real                ) ] :Optional  :TiltImage: TiltAxisAngle TiltAngle\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :Configuration File\n");
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
