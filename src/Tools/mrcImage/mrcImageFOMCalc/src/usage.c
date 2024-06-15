#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Optional  :TestData\n");
    fprintf(stderr, "    [-w[eight]           Weight              (1.0       ).as(Real                ) ] :Optional  :Weight\n");
    fprintf(stderr, "    [-I[nput]            InList              (NULL      ).as(inFileList          ) ] :Optional  :TestData Set\n");
    fprintf(stderr, "    [-r[ef]              Ref                 (NULL      ).as(inFile              ) ] :Essential :Ref, Model Data\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output: \n");
    fprintf(stderr, "    [-RR[ange]           Rmin                (0.0       ).as(Real                ) \n                         Rmax                (0.1       ).as(Real                ) ] :Optional  :Ring Range\n");
    fprintf(stderr, "    [-dR[ange]           dR                  (0.0       ).as(Real                ) ] :Optional  :Ring Width\n");
    fprintf(stderr, "    [-nS[ector]          nSector             (1         ).as(Integer             ) ] :Optional  :Sector Number\n");
    fprintf(stderr, "    [-dA[lpha]           dAlpha              (5         ).as(Real                ) ] :Optional  :delta Alpha\n");
    fprintf(stderr, "    [-XMax               XMax                (0.0       ).as(Real                ) ] :Optional  :Xmax: If not set, one calc Xmax\n");
    fprintf(stderr, "    [-A[uto]S[cale]                                                                ] :Optional  :Auto Scaling\n");
    fprintf(stderr, "    [-A[llArea]A[uto]S[cale]AASRMax             (0.05      ).as(Real                ) ] :Optional  :All Area Auto Scaling\n");
    fprintf(stderr, "    [-RS[cale]                                                                     ] :Optional  :R Scaling\n");
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