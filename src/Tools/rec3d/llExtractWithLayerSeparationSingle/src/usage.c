#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFileList          ) ] :Essential :InputDataFile[fft:mrcImage etc]\n");
    fprintf(stderr, "    [-r[eference]        Ref                 (NULL      ).as(inFile              ) ] :Essential :Input Reference[ll]\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFileList         ) ] :Essential :OutputDataFile[ll]\n");
    fprintf(stderr, "    [-phi                phiMin              (0.0       ).as(Real                ) \n                         phiMax              (360.0     ).as(Real                ) \n                         phiDelta            (5.0       ).as(Real                ) ] :Optional  :Phi[degree]\n");
    fprintf(stderr, "    [-z                  zMin                (0.0       ).as(Real                ) \n                         zMax                (360.0     ).as(Real                ) \n                         zDelta              (5.0       ).as(Real                ) ] :Optional  :z[A]\n");
    fprintf(stderr, "    [-r                  rMin                (1.        ).as(Real                ) \n                         rMax                (1.        ).as(Real                ) \n                         rDelta              (0.1       ).as(Real                ) ] :Optional  :r[ratio]\n");
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
