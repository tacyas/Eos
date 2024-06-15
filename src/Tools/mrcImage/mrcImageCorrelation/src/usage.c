#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile: Correlation Map\n");
    fprintf(stderr, "    [-O[utput]           Out2                (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile: Correlation Map for Refinement\n");
    fprintf(stderr, "    [-r[eference]        Ref                 (NULL      ).as(inFile              ) ] :Essential :ReferenceDataFile\n");
    fprintf(stderr, "    [-cor[relation]Info  OutCor              (stdout    ).as(outFile             ) ] :Optional  :Output: Correlation Info\n");
    fprintf(stderr, "    [-a[verage]          Avg                 (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile: Averaged File\n");
    fprintf(stderr, "    [-s[hit]             Shift               (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile: Shifted InputFile\n");
    fprintf(stderr, "    [-refine             RefineStep          (0.25      ).as(Real                ) \n                         RefineRange         (3.0       ).as(Real                ) \n                         RefineMode          (2         ).as(Integer             ) ] :Optional  :Refinemnet: Step Range[pixelUnit]\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-M[ode2]            mode2               (0         ).as(Integer             ) ] :Optional  :Mode2\n");
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
