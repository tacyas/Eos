#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-t[itle]            Title               (NULL      ).as(String              ) ] :Optional  :Title\n");
    fprintf(stderr, "    [-d[elta]            delta               (2.5       ).as(Real                ) ] :Optional  :delta[A]\n");
    fprintf(stderr, "    [-C                  RepeatDistance      (2.5       ).as(Real                ) ] :Optional  :RepeatDistance[A]\n");
    fprintf(stderr, "    [-r[Max]             rMax                (2.5       ).as(Real                ) ] :Optional  :rMax[A]\n");
    fprintf(stderr, "    [-p[hiStart]         phiStart            (0         ).as(Real                ) ] :Optional  :phiStart[degree]\n");
    fprintf(stderr, "    [-zmi[n]             zMin                (0.0       ).as(Real                ) ] :Optional  :zMin\n");
    fprintf(stderr, "    [-zma[x]             zMax                (55.0      ).as(Real                ) ] :Optional  :zMax\n");
    fprintf(stderr, "    [-zde[lta]           deltaz              (2.5       ).as(Real                ) ] :Optional  :deltaz\n");
    fprintf(stderr, "    [-w[eight]           WeightOf0thLayer    (0.5       ).as(Real                ) ] :Optional  :WeightOf0thLayer\n");
    fprintf(stderr, "    [-l[Weight]          Layer               (NULL      ).as(inFile              ) ] :Optional  :Layer WeightOfEachLayer\n");
    fprintf(stderr, "    [-f9[9]                                                                        ] :Optional  :IF(NN(LL)!=NL(LL)) WT(LL) = 0.0\n");
    fprintf(stderr, "    [-O[ffset]           CUT                 (0.5       ).as(Real                ) ] :Optional  :CUT\n");
    fprintf(stderr, "    [-a[mean]            Mean                (0.0       ).as(Real                ) ] :Optional  :Mean\n");
    fprintf(stderr, "    [-s[igma]            Sigma               (0.0       ).as(Real                ) ] :Optional  :Sigma\n");
    fprintf(stderr, "    [-I[nverse]                                                                    ] :Optional  :Nega-Posi Reverse\n");
    fprintf(stderr, "    [-n[otInteractive]                                                             ] :Optional  :not Intaracitve\n");
    fprintf(stderr, "    [-AntiPole                                                                     ] :Optional  :Anti Pole: zmax -> zmin:  Else zmin->zmax\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :\n\t\t\t\t0: Normarize\n\t\t\t\t1: Not Normarize bu edge average is zero.\n\t\t\t\t2: Not Normarize\n\t\t\t\tdefalt: 0\n");
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
