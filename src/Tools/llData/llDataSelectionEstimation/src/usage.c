#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i1[nput]           N1                  (0         ).as(Real                ) \n                         L1                  (161       ).as(Real                ) ] :Essential :Input: N L\n");
    fprintf(stderr, "    [-i2[nput]           N2                  (14        ).as(Real                ) \n                         L2                  (12        ).as(Real                ) ] :Essential :Input: N L\n");
    fprintf(stderr, "    [-tmax               tmax                (100       ).as(Real                ) ] :Optional  :Input: tmax\n");
    fprintf(stderr, "    [-umax               umax                (200       ).as(Real                ) ] :Optional  :Input: umax\n");
    fprintf(stderr, "    [-r[accept]          r                   (0.1       ).as(Real                ) ] :Optional  :Input: acceptable residue\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
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
