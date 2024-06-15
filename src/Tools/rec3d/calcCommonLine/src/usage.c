#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Optional  :InputEulerAnglesList\n");
    fprintf(stderr, "    [-R[ot]1             EMode1              (YOYS      ).as(String              ) \n                         Rot1_1              (0.0       ).as(Real                ) \n                         Rot1_2              (0.0       ).as(Real                ) \n                         Rot1_3              (0.0       ).as(Real                ) ] :Optional  :Input: RotAngle1[degree]\n");
    fprintf(stderr, "    [-R[ot]2             EMode2              (YOYS      ).as(String              ) \n                         Rot2_1              (0.0       ).as(Real                ) \n                         Rot2_2              (0.0       ).as(Real                ) \n                         Rot2_3              (0.0       ).as(Real                ) ] :Optional  :Input: RotAngle2[degree]\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output:Degrees\n");
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
