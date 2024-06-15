#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (stdin     ).as(inFileList::mrcImage) ] :Essential :Input: Ins\n");
    fprintf(stderr, "    [-r[eferenc]         Ref                 (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input: Ref\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile::mrcImage   ) ] :Essential :Output:Average\n");
    fprintf(stderr, "    [-range              Min                 (0.0       ).as(Real                ) \n                         Max                 (360.0     ).as(Real                ) \n                         Delta               (5.0       ).as(Real                ) \n                         Iter                (2         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-iter               iter                (2         ).as(Integer             ) ] :Optional  :iteration for rotation\n");
    fprintf(stderr, "    [-M[odeCorrelation]  CorMode             (16        ).as(Integer             ) ] :Optional  :Mode: Correlation\n");
    fprintf(stderr, "    [-Method[Correlation]Method              (0         ).as(Integer             ) ] :Optional  :Method: Correlation\n");
    fprintf(stderr, "    [-Periodic                                                                     ] :Optional  :Periodic\n");
    fprintf(stderr, "    [-maxIter[aration]   maxIter             (10        ).as(Integer             ) ] :Optional  :MaxIteration\n");
    fprintf(stderr, "    [-rmsd               rmsd                (1e-2      ).as(Real                ) ] :Optional  :rmsd\n");
    fprintf(stderr, "    [-log                Log                 (stdout    ).as(outFile::ASCII      ) ] :Optional  :logFile\n");
    fprintf(stderr, "    [-thres[hold]        Thres               (0.2       ).as(Real                ) ] :Optional  :threshold: Linear Correlation\n");
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
