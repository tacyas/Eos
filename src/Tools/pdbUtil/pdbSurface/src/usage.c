#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: pdbFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output: pdbFile\n");
    fprintf(stderr, "    [-order              order               (1.7       ).as(Real                ) ] :Optional  :Order: [A]\n");
    fprintf(stderr, "    [-refine             refine              (2         ).as(Integer             ) ] :Optional  :Refine: Meshsize = Order/Refine\n");
    fprintf(stderr, "    [-size               size                (3         ).as(Integer             ) ] :Optional  :Refine: Shell thickness = Order/Refine*Size\n");
    fprintf(stderr, "    [-weight             weight              (100.0     ).as(Real                ) ] :Optional  :Weight\n");
    fprintf(stderr, "    [-mergin             mergin              (3.0       ).as(Real                ) ] :Optional  :SearchArea\n");
    fprintf(stderr, "    [-thres              thresHold           (0.0       ).as(Real                ) ] :Optional  :thresHold\n");
    fprintf(stderr, "    [-densityMode        DensityMode         (0         ).as(Integer             ) ] :Optional  :DensityMode\n");
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
