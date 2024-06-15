#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-dz[deltaz]         dz                  (27.3      ).as(Real                ) ] :Optional  :deltaz(A)\n");
    fprintf(stderr, "    [-dp[deltaphi]       dphi                (13.84     ).as(Real                ) ] :Optional  :deltaphi(degree)\n");
    fprintf(stderr, "    [-sz[startz]         sz                  (0         ).as(Integer             ) ] :Optional  :startz(pixel)\n");
    fprintf(stderr, "    [-ez[startz]         ez                  (0         ).as(Integer             ) ] :Optional  :endz(pixel)\n");
    fprintf(stderr, "    [-sphi[startphi]     sphi                (0         ).as(Real                ) ] :Optional  :startphi(degree) for masking\n");
    fprintf(stderr, "    [-ephi[startphi]     ephi                (90        ).as(Real                ) ] :Optional  :endphi(degree) for masking\n");
    fprintf(stderr, "    [-v[alue]            value               (0         ).as(Real                ) ] :Optional  :value to pad\n");
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