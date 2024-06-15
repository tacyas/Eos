#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: mrc(3D)\n");
    fprintf(stderr, "    [-t[emplate]         Template            (NULL      ).as(inFile              ) ] :Essential :Input: mrcFFT(2D)\n");
    fprintf(stderr, "    [-i[nput]Pri[or]     InPri               (NULL      ).as(inFile              ) ] :Optional  :Input:: \n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Essential :Output: filelist\n");
    fprintf(stderr, "    [-EulerMode          EulerMode           (YOYS      ).as(String              ) ] :Optional  :Input: EulerMode\n");
    fprintf(stderr, "    [-Rot1               Rot1Start           (0.0       ).as(Real                ) \n                         Rot1End             (360.0     ).as(Real                ) \n                         Rot1Delta           (10        ).as(Real                ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-Rot2               Rot2Start           (0.0       ).as(Real                ) \n                         Rot2End             (360.0     ).as(Real                ) \n                         Rot2Delta           (10        ).as(Real                ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-Rot3               Rot3Start           (0.0       ).as(Real                ) \n                         Rot3End             (360.0     ).as(Real                ) \n                         Rot3Delta           (10        ).as(Real                ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-trans[late]        TransX              (0.0       ).as(Real                ) \n                         TransY              (0.0       ).as(Real                ) ] :Optional  :Input: Translation\n");
    fprintf(stderr, "    [-InterpMode         InterpMode          (0         ).as(Integer             ) ] :Optional  :Interpolation Mode\n");
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
