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
    fprintf(stderr, "    [-s[igma]D[ensity]   SigmaDensity        (2.0       ).as(Real                ) ] :Optional  :SigmaDensity\n");
    fprintf(stderr, "    [-k[ernal]T[type]D[ensity]KernelTypeDensity   (0         ).as(Integer             ) ] :Optional  :KernelTypeForDensity\n");
    fprintf(stderr, "    [-s[igma]S[pace]     SigmaSpace          (1.0       ).as(Real                ) ] :Optional  :SigmaSpace\n");
    fprintf(stderr, "    [-s[igma]S[pace]3    SigmaSpaceX         (1.0       ).as(Real                ) \n                         SigmaSpaceY         (1.0       ).as(Real                ) \n                         SigmaSpaceZ         (1.0       ).as(Real                ) ] :Optional  :SigmaSpace(3D)\n");
    fprintf(stderr, "    [-k[ernel]T[ype]S[pace]KernelTypeSpace     (0         ).as(Integer             ) ] :Optional  :KernelTypeForSpace\n");
    fprintf(stderr, "    [-k[ernel]S[ize]     KernelSize          (5         ).as(Integer             ) ] :Optional  :KernelSize\n");
    fprintf(stderr, "    [-k[ernel]S[ize]3    KernelSizeX         (5         ).as(Integer             ) \n                         KernelSizeY         (5         ).as(Integer             ) \n                         KernelSizeZ         (5         ).as(Integer             ) ] :Optional  :KernelSize(3D)\n");
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
