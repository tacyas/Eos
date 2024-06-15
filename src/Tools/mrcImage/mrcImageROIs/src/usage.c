#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-I[nformation]      Info                (NULL      ).as(inFile              ) ] :Essential :Information\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Optional  :MontageFile\n");
    fprintf(stderr, "    [-S[hrink]           Shrink              (NULL      ).as(Integer             ) ] :Optional  :When inputimage was shrunk\n");
    fprintf(stderr, "    [-width              Width               (0.0       ).as(Real                ) ] :Optional  :Width\n");
    fprintf(stderr, "    [-height             Height              (0.0       ).as(Real                ) ] :Optional  :Height\n");
    fprintf(stderr, "    [-NonPeriodic                                                                  ] :Optional  :Zero Outof Range\n");
    fprintf(stderr, "    [-PadMode            PadMode             (0         ).as(Integer             ) ] :Optional  :PadMode(refer to mrcImagePad)\n");
    fprintf(stderr, "    [-M[ode]             Mode                (2         ).as(Integer             ) ] :Optional  :ImageType:0 byte 1 short 2 float\n");
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
