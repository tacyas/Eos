#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-I[nput]1           In1                 (NULL      ).as(inFileListNoOpen    ) ] :Optional  :InputDataFileList1 : normal correlation\n");
    fprintf(stderr, "    [-I[nput]2           In2                 (NULL      ).as(inFileListNoOpen    ) ] :Optional  :InputDataFileList2 : derivation1D correlation\n");
    fprintf(stderr, "    [-I[nput]3           In3                 (NULL      ).as(inFileListNoOpen    ) ] :Optional  :InputDataFileList3 : derivation2D correlation\n");
    fprintf(stderr, "    [-I[nput]4           In4                 (NULL      ).as(inFileListNoOpen    ) ] :Optional  :InputDataFileList4 : length correlation\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-M[ode]             Mode                (15        ).as(Integer             ) ] :Optional  :Mode : choice of used Correlation\n");
    fprintf(stderr, "    [-v[ariance]         variance            (5         ).as(Real                ) ] :Optional  :variance of Gaussian weight function\n");
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
