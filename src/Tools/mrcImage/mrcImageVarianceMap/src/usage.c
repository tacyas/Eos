#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFileList          ) ] :Optional  :In: InputList\n");
    fprintf(stderr, "    [-I[nput]            In2                 (NULL      ).as(inFile              ) \n                         In2Var              (NULL      ).as(inFile              ) \n                         In2N                (0         ).as(Integer             ) ] :Optional  :In: Input\n");
    fprintf(stderr, "    [-Nor[malizingParameter]NorA                (0.0       ).as(Real                ) \n                         NorB                (1.0       ).as(Real                ) ] :Optional  :In: A + B*x: NormalizingParameter\n");
    fprintf(stderr, "    [-r[ef]              Ref                 (NULL      ).as(inFileList          ) ] :Optional  :Ref: InputList\n");
    fprintf(stderr, "    [-R[ef]              Ref2                (NULL      ).as(inFile              ) \n                         Ref2Var             (NULL      ).as(inFile              ) \n                         Ref2N               (0         ).as(Integer             ) ] :Optional  :Ref: Input\n");
    fprintf(stderr, "    [-Nor[malizingParameter]RNorARef             (0.0       ).as(Real                ) \n                         NorBRef             (1.0       ).as(Real                ) ] :Optional  :In: A + B*x: NormalizingParameter for Ref\n");
    fprintf(stderr, "    [-I[and]R            InAndRef2           (NULL      ).as(inFile              ) \n                         InAndRef2Var        (NULL      ).as(inFile              ) \n                         InAndRef2N          (0         ).as(Integer             ) ] :Optional  :In and Ref: Input\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Optional  :Output: Variance Probability\n");
    fprintf(stderr, "    [-v[arianceMap]      OutV                (NULL      ).as(outFile             ) ] :Optional  :Output: Variance Map\n");
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
