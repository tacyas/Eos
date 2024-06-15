#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (stdin     ).as(inFile              ) ] :Optional  :Input: ASCII\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output: mrcImage\n");
    fprintf(stderr, "    [-nx                 Nx                  (512       ).as(Integer             ) ] :Essential :ImageSize: x\n");
    fprintf(stderr, "    [-ny                 Ny                  (512       ).as(Integer             ) ] :Optional  :ImageSize: y\n");
    fprintf(stderr, "    [-nz                 Nz                  (1         ).as(Integer             ) ] :Optional  :ImageSize: z\n");
    fprintf(stderr, "    [-sx                 Sx                  (3         ).as(Integer             ) ] :Essential :FilterSize: x\n");
    fprintf(stderr, "    [-sy                 Sy                  (3         ).as(Integer             ) ] :Optional  :FilterSize: y\n");
    fprintf(stderr, "    [-sz                 Sz                  (1         ).as(Integer             ) ] :Optional  :FilterSize: z\n");
    fprintf(stderr, "    [-v[erbose]                                                                    ] :Optional  :Verbose\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-M[ode]             Mode                (0         ).as(Integer             ) ] :Optional  :Mode: Filter shape\n");
    fprintf(stderr, "    [-m[ode]             mode                (2         ).as(Integer             ) ] :Optional  :mode: output mrc\n");
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
