#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (stdin     ).as(inFile              ) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-oP[utput]          Out2                (NULL      ).as(outFile             ) ] :Optional  :OutputParameter\n");
    fprintf(stderr, "    [-kV                 kV                  (200       ).as(Real                ) ] :Optional  :kV\n");
    fprintf(stderr, "    [-Cs                 Cs                  (1.7       ).as(Real                ) ] :Optional  :Cs[mm]\n");
    fprintf(stderr, "    [-Def                minDef              (0.0       ).as(Real                ) \n                         maxDef              (200000.0  ).as(Real                ) \n                         delDef              (1000.0    ).as(Real                ) ] :Optional  :Def[A]\n");
    fprintf(stderr, "    [-Amp                minAmp              (0.0       ).as(Real                ) \n                         maxAmp              (0.4       ).as(Real                ) \n                         delAmp              (0.005     ).as(Real                ) ] :Optional  :AmpToPhase\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-R[/A]              R                   (NULL      ).as(Real                ) ... ] :Variable  :ThonRing[/A]\n");
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
