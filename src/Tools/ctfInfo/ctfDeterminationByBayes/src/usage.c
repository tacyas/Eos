#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-i[nput]2           In2                 (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-i[nput]3           In3                 (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-i[nput]4           In4                 (NULL      ).as(inFileListNoOpen    ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-n[um]              numDistribution     (3         ).as(Integer             ) \n                         numLikelihood       (3         ).as(Integer             ) ] :Essential :Integer\n");
    fprintf(stderr, "    [-rmax               rmax                (250       ).as(Real                ) ] :Optional  :rmax[1/A]\n");
    fprintf(stderr, "    [-rintermediate      rintermediate       (250       ).as(Real                ) ] :Optional  :rintermediate[1/A]\n");
    fprintf(stderr, "    [-rfiestpeak         rfirstpeak          (0.001     ).as(Real                ) ] :Optional  :rfirstpeak[1/A]\n");
    fprintf(stderr, "    [-rmin               rmin                (0         ).as(Real                ) ] :Optional  :rmin[1/A]\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-MTFmode            MTFmode             (0         ).as(Integer             ) ] :Optional  :MTFmode\n");
    fprintf(stderr, "    [-Ainmode            Ainmode             (0         ).as(Integer             ) ] :Optional  :Ainmode\n");
    fprintf(stderr, "    [-Intensitymode      Intensitymode       (0         ).as(Integer             ) ] :Optional  :Intensitymode\n");
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
