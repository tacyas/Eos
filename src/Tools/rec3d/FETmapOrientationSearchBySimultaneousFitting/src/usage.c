#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            InML                (NULL      ).as(inFile              ) ] :Essential :InputMapList\n");
    fprintf(stderr, "    [-i[nput]n[ame]      InNL                (NULL      ).as(inFile              ) ] :Essential :InputNameList\n");
    fprintf(stderr, "    [-i[nput]C[ore]L[ist]InCL                (NULL      ).as(inFile              ) ] :Essential :InputCandidateCoreList\n");
    fprintf(stderr, "    [-P[eakArea]M[ode]   PM                  (0         ).as(Integer             ) ] :Optional  :PeakDetectAreaMode\n");
    fprintf(stderr, "    [-P[eak]N[umber]     PN                  (10        ).as(Integer             ) ] :Optional  :PeakNumber\n");
    fprintf(stderr, "    [-PDT[hres]          PDT                 (0.2       ).as(Real                ) ] :Optional  :PeakDetectThreshold_ForMode0\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
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
