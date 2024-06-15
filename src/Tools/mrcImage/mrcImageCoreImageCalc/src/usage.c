#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: Pretreated Core-loss Image\n");
    fprintf(stderr, "    [-e[neryg]l[oss]     EL                  (180       ).as(Real                ) ] :Essential :Input: EnergyLoss\n");
    fprintf(stderr, "    [-bg[List]           BG                  (NULL      ).as(inFileList          ) ] :Essential :Input: Bg File List\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output: Core-Loss Image\n");
    fprintf(stderr, "    [-O[utputBG]         OutBG               (NULL      ).as(outFile             ) ] :Optional  :Output: BG-Image\n");
    fprintf(stderr, "    [-Chi[sq]            OutChi              (NULL      ).as(outFile             ) ] :Optional  :Output: Chi-Image\n");
    fprintf(stderr, "    [-initial[Value]     A1                  (5040      ).as(Real                ) \n                         A2                  (500       ).as(Real                ) \n                         A3                  (-12       ).as(Real                ) ] :Optional  :Input: A1 + A2*EELS^A3\n");
    fprintf(stderr, "    [-limitA3            LimitA3Min          (-16       ).as(Real                ) \n                         LimitA3Max          (-5        ).as(Real                ) ] :Optional  :Input: limit A3\n");
    fprintf(stderr, "    [-baseEELS           BaseEELS            (160.0     ).as(Real                ) ] :Optional  :Input: BaseEELS as 1.0\n");
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
