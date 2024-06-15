#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: mrc\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output: mrc\n");
    fprintf(stderr, "    [-param[eter]o[utput]OutParams           (stdout    ).as(outFile             ) ] :Optional  :Output: ASCII\n");
    fprintf(stderr, "    [-v[alueForCut]      cutValue            (3.0       ).as(Real                ) ] :Optional  :CutValue/Sigma\n");
    fprintf(stderr, "    [-u[nsigned]         UnsignedMax         (65535     ).as(Real                ) \n                         UnsignedHalf        (16384     ).as(Real                ) ] :Optional  :Unsigned to Signed: Need Max\n");
    fprintf(stderr, "    [-thres              Threshold           (0.5       ).as(Real                ) ] :Optional  :Threshold for Low/High value area \n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-P[attern]          Pattern             (0         ).as(Integer             ) ] :Optional  :Mode2:AbnormalPattern\n");
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
