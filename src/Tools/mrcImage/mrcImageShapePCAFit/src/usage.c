#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: test(mrcImage)\n");
    fprintf(stderr, "    [-r[eference]        Ref                 (NULL      ).as(inFile              ) ] :Essential :Input: ref(mrcImage)\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output: Parameters\n");
    fprintf(stderr, "    [-fit                Fit                 (NULL      ).as(outFile             ) ] :Optional  :Output: fit(mrcImage) <- test \n");
    fprintf(stderr, "    [-fitMat             FitMat              (NULL      ).as(outFile             ) ] :Optional  :Output: Matrix3D for fit(mrcImage) <- test \n");
    fprintf(stderr, "    [-iMode              IMode               (2         ).as(Integer             ) ] :Optional  :InterpolationMode\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-C[ontour]          Contour             (1.0       ).as(Real                ) ... ] :Variable  :Contour(test/ref)\n");
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
