#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFileListNoOpen    ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-nx                 Nx                  (10        ).as(Integer             ) ] :Optional  :Nx: If this option does not set, the default value will be set\n");
    fprintf(stderr, "    [-ny                 Ny                  (10        ).as(Integer             ) ] :Optional  :Ny: If this option does not set, the value will be set automatically\n");
    fprintf(stderr, "    [-W[idth]            Width               (10        ).as(Integer             ) ] :Optional  :Width: If this option does not set, the value will be set automatically\n");
    fprintf(stderr, "    [-H[eight]           Height              (10        ).as(Integer             ) ] :Optional  :Height: If this option does not set, the value will be set automatically\n");
    fprintf(stderr, "    [-AW[indow]          AvgWnd              (2000      ).as(Real                ) ] :Optional  :AverageWindow for Pad\n");
    fprintf(stderr, "    [-V[alue]            Value               (0.0       ).as(Real                ) ] :Optional  :\n");
    fprintf(stderr, "    [-P[ad]M[ode]        PadMode             (3         ).as(Integer             ) ] :Optional  :\n");
    fprintf(stderr, "    [-EdgeAverage                                                                  ] :Optional  :\n");
    fprintf(stderr, "    [-EdgeAverageWindow  EdgeAverageWindow   (4         ).as(Integer             ) ] :Optional  :Definition of Edge\n");
    fprintf(stderr, "    [-NoAverage                                                                    ] :Optional  :\n");
    fprintf(stderr, "    [-Max                Max                 (16383     ).as(Real                ) ] :Optional  :MaximumValue: If the pixel value is more than this max, the pixel value is assigned to the Value indicated by -V or -VMax.\n");
    fprintf(stderr, "    [-VMax               VMax                (16383     ).as(Real                ) ] :Optional  :Attention: related to -Max \n");
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
