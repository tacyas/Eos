#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile::ASCII      ) ] :Optional  :Output:FNC\n");
    fprintf(stderr, "    [-d[elta]            delta               (0.0       ).as(Real                ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-C[enter]           Centre              (0         ).as(Integer             ) ] :Optional  :CentreMode\n");
    fprintf(stderr, "    [-M[ode]             GetMode             (0         ).as(Integer             ) ] :Optional  :PixelDataGetHowToGet: InterpolationMode \n");
    fprintf(stderr, "    [-FSC                                                                          ] :Optional  :Output:predicted FSC\n");
    fprintf(stderr, "    [-Cref                                                                         ] :Optional  :Output:Cref\n");
    fprintf(stderr, "    [-FSCfull                                                                      ] :Optional  :Output:FSC full\n");
    fprintf(stderr, "    [-NoiseWeighted      Brestore            (0.0       ).as(Real                ) ] :Optional  :NoiseWeighted: Cref*exp(-Brestore/(4*d^2)\n");
    fprintf(stderr, "    [-mask               InMask              (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input: Mask for FSC\n");
    fprintf(stderr, "    [-maskBack           InBackMask          (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input: Mask for FSC Back\n");
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
