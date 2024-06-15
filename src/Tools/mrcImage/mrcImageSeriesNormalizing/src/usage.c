#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFileList          ) ] :Essential :Input: name list of mrcImage\n");
    fprintf(stderr, "    [-i[nput]w[eight]    Weight              (NULL      ).as(inFile              ) ] :Optional  :weight: list of 0 or 1 \n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFileList         ) ] :Essential :Output: name list of mrcImage\n");
    fprintf(stderr, "    [-param[eters]       Param               (stdout    ).as(outFile             ) ] :Optional  :Output: Parameters\n");
    fprintf(stderr, "    [-Low[ValueArea]     thresOfLowValueArea (0.01      ).as(Real                ) ] :Optional  :LowValueArea: rate\n");
    fprintf(stderr, "    [-High[ValueArea]    thresOfHighValueArea(0.99      ).as(Real                ) ] :Optional  :HighValueArea: rate\n");
    fprintf(stderr, "    [-L[ow]              Low                 (0.1       ).as(Real                ) ] :Optional  :Low\n");
    fprintf(stderr, "    [-H[igh]             High                (0.9       ).as(Real                ) ] :Optional  :High\n");
    fprintf(stderr, "    [-UseLH              UseLow              (1         ).as(Integer             ) \n                         UseHigh             (1         ).as(Integer             ) ] :Optional  :Use Low and High\n");
    fprintf(stderr, "    [-Low[ValueArea]Exp  ALow                (1.0       ).as(Real                ) \n                         KLow                (0.1       ).as(Real                ) \n                         BLow                (1.0       ).as(Real                ) ] :Optional  :Alow * exp(-Klow * i) + Blow\n");
    fprintf(stderr, "    [-High[ValueArea]Exp AHigh               (0.1       ).as(Real                ) \n                         KHigh               (0.1       ).as(Real                ) \n                         BHigh               (0.0       ).as(Real                ) ] :Optional  :Ahigh * exp(-Khigh * i) + Bhigh\n");
    fprintf(stderr, "    [-maxIter            maxIter             (100       ).as(Integer             ) ] :Optional  :maxIteration\n");
    fprintf(stderr, "    [-xtol               xtol                (1e-8      ).as(Real                ) ] :Optional  :xtol\n");
    fprintf(stderr, "    [-gtol               gtol                (1e-8      ).as(Real                ) ] :Optional  :gtol\n");
    fprintf(stderr, "    [-ftol               ftol                (0.0       ).as(Real                ) ] :Optional  :ftol\n");
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
