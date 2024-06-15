#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            InList              (NULL      ).as(inFileListNoOpen    ) ] :Essential :Input: filelist\n");
    fprintf(stderr, "    [-o[utput]           OutList             (NULL      ).as(outFileListNoOpen   ) ] :Essential :Output: filelist\n");
    fprintf(stderr, "    [-EPS                EPS                 (1e2       ).as(Real                ) ] :Optional  :EPS: lambda<EPS, stop calculation. \n");
    fprintf(stderr, "    [-NX                 NX                  (30        ).as(Integer             ) ] :Optional  :NX: pixcelNX \n");
    fprintf(stderr, "    [-NY                 NY                  (30        ).as(Integer             ) ] :Optional  :NY: pixcelNX \n");
    fprintf(stderr, "    [-O[utput]           Outvector           (NULL      ).as(outFile             ) ] :Optional  :Output: vectorfile\n");
    fprintf(stderr, "    [-EPSO[utput]        EPSOutcaletime      (NULL      ).as(outFile             ) ] :Optional  :EPSOutput: caletimefile\n");
    fprintf(stderr, "    [-E[igenImage]       EigenImage          (eigen     ).as(String              ) ] :Optional  :Output: eigenImage\n");
    fprintf(stderr, "    [-numE[igenImage]    numOfEigenImage     (10        ).as(Integer             ) ] :Optional  :Number of eigenImages\n");
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
