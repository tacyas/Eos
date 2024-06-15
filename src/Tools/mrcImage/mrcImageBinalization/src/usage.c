#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input:mrcImage\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile::mrcImage   ) ] :Essential :Output:mrcImage\n");
    fprintf(stderr, "    [-O[utput]           OutParam            (stdout    ).as(outFile::ASCII      ) ] :Optional  :Output:Parameters\n");
    fprintf(stderr, "    [-t[hreshold]        t                   (0         ).as(Real                ) ] :Optional  :Value of threshold\n");
    fprintf(stderr, "    [-d[elta]t[hreshold] deltaThreshold      (0         ).as(Real                ) ] :Optional  :Difference threshold\n");
    fprintf(stderr, "    [-s[igma]t[hreshold] sigmaThreshold      (0.5       ).as(Real                ) ] :Optional  :Sigma threshold(BandPath)\n");
    fprintf(stderr, "    [-v[alue]            v                   (0         ).as(Real                ) ] :Optional  :Value\n");
    fprintf(stderr, "    [-near               near                (0         ).as(Real                ) ] :Optional  :Near[pixel]: Near-area also binary\n");
    fprintf(stderr, "    [-nLevel             nLevel              (256       ).as(Integer             ) ] :Optional  :nLevel: For creating histgram by Kittler and Ohtsu \n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-p[tile]            p                   (0.5       ).as(Real                ) ] :Optional  :p\n");
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
