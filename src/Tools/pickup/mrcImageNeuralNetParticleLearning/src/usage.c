#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]p[ositive]  InPositive          (NULL      ).as(inFileList          ) ] :Essential :Input: partile image list filename\n");
    fprintf(stderr, "    [-i[nput]n[egative]  InNegative          (NULL      ).as(inFileList          ) ] :Essential :Input: background image list filename\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFileList         ) ] :Essential :Output: Neural Net Parameters after Learning\n \t\t\tFileNameOfWeightForTheBelowLayer NumOfCellOfThisLayer BiasOfThisLayer\n");
    fprintf(stderr, "    [-B[ias0]            Bias                (1.0       ).as(Real                ) ] :Optional  :Bias: The value of the bias of the input layer\n");
    fprintf(stderr, "    [-max[Counter]       MaxCounter          (10        ).as(Integer             ) ] :Optional  :MaxCounter\n");
    fprintf(stderr, "    [-EPS                EPS                 (0.005     ).as(Real                ) ] :Optional  :Final Error\n");
    fprintf(stderr, "    [-lambda             Lambda              (0.1       ).as(Real                ) ] :Optional  :step for backpropagation\n");
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
