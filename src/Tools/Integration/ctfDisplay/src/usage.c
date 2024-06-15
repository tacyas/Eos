#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            inMRC               (NULL      ).as(inFile              ) ] :Optional  :Input:MRC(FFT)\n");
    fprintf(stderr, "    [-o[utput]           outCTF              (stdout    ).as(appendFile          ) ] :Optional  :Input/Output: ctfinfo\n");
    fprintf(stderr, "    [-Rmax               Rmax                (0.2       ).as(Real                ) ] :Optional  :Rmax [A-1] \n");
    fprintf(stderr, "    [-Imax               Imax                (0.2       ).as(Real                ) ] :Optional  :Intensity: min-max\n");
    fprintf(stderr, "    [-Imin               Imin                (0.02      ).as(Real                ) ] :Optional  :Intensity: min-max\n");
    fprintf(stderr, "    [-AutoRange                                                                    ] :Optional  :Intensity: min-max\n");
    fprintf(stderr, "    [-Log                                                                          ] :Optional  :Log of Intensity\n");
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
