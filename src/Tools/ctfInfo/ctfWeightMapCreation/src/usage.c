#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-kV                 kV                  (200       ).as(Real                ) ] :Optional  :AccVol[kV]\n");
    fprintf(stderr, "    [-Cs                 Cs                  (1.7       ).as(Real                ) ] :Optional  :Cs[mm]\n");
    fprintf(stderr, "    [-df                 Defocus             (2.7       ).as(Real                ) ] :Essential :Defocus[A]:under(+)\n");
    fprintf(stderr, "    [-white              WhiteNoise          (1.0       ).as(Real                ) ] :Optional  :WhiteNoise(N/S)\n");
    fprintf(stderr, "    [-noise              Noise               (NULL      ).as(inFile              ) ] :Optional  :Noise Power Spectrum\n");
    fprintf(stderr, "    [-splusn             SplusN              (NULL      ).as(inFile              ) ] :Optional  :Signal+Noise Power Spectrum\n");
    fprintf(stderr, "    [-dRinv              dRinv               (1024*5/3  ).as(Real                ) ] :Essential :dRinv[A]\n");
    fprintf(stderr, "    [-dRmaxInv           dRmaxInv            (10.0      ).as(Real                ) ] :Essential :dRmaxInv[A]\n");
    fprintf(stderr, "    [-SinWin             SinWinRminInv       (20.0      ).as(Real                ) \n                         SinWinRmaxInv       (10.0      ).as(Real                ) ] :Optional  :RminInv[A] RmaxInv[A]\n");
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
