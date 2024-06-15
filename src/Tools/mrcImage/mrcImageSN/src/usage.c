#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFileListNoOpen    ) ] :Essential :InputList\n");
    fprintf(stderr, "    [-A[verage]          Avg                 (NULL      ).as(outFile             ) ] :Optional  :Output: Average\n");
    fprintf(stderr, "    [-TrimmedA[verage]   TrimmedAvg          (NULL      ).as(outFile             ) ] :Optional  :Output: TrimmedAverage\n");
    fprintf(stderr, "    [-M[edian]           Median              (NULL      ).as(outFile             ) ] :Optional  :Output: Median\n");
    fprintf(stderr, "    [-SN                 SN                  (NULL      ).as(outFile             ) ] :Optional  :Output: SN:=Average/SD\n");
    fprintf(stderr, "    [-t                  t                   (NULL      ).as(outFile             ) ] :Optional  :Output: t=:Average/SD/sqrt(n-2)\n");
    fprintf(stderr, "    [-SE                 SE                  (NULL      ).as(outFile             ) ] :Optional  :Output: Standard Error\n");
    fprintf(stderr, "    [-SD                 SD                  (NULL      ).as(outFile             ) ] :Optional  :Output: Standard Deviation\n");
    fprintf(stderr, "    [-Var                Var                 (NULL      ).as(outFile             ) ] :Optional  :Output: Variance\n");
    fprintf(stderr, "    [-Trimmed            TrimmedRange        (0.1       ).as(Real                ) ] :Optional  :TrimmedRange::Real\n");
    fprintf(stderr, "    [-c[onfigFile]       configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
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
