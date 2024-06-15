#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: mrcImage[3D]\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Optional  :Output: mrcImage[2D]\n");
    fprintf(stderr, "    [-fileList           filenamePrefix      (2D        ).as(String              ) \n                         filenameSuffix      (2d        ).as(String              ) \n                         filenameFormat      (%%s-%%05d.%%s).as(String              ) ] :Optional  :Output: mrcImage[2D] List \n");
    fprintf(stderr, "    [-Rot1               Rot1Start           (0.0       ).as(Real                ) \n                         Rot1End             (360.0     ).as(Real                ) \n                         Rot1Delta           (10        ).as(Real                ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-Rot2               Rot2Start           (0.0       ).as(Real                ) \n                         Rot2End             (360.0     ).as(Real                ) \n                         Rot2Delta           (10        ).as(Real                ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-Rot3               Rot3Start           (0.0       ).as(Real                ) \n                         Rot3End             (360.0     ).as(Real                ) \n                         Rot3Delta           (10        ).as(Real                ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-EulerMode          EulerMode           (ZOYS      ).as(String              ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-InterpolationMode  InterpolationMode   (1         ).as(Integer             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-AreaMode           AreaMode            (0         ).as(Integer             ) ] :Optional  :Cubic: 0, Globular: 1 \n");
    fprintf(stderr, "    [-pthread            pthreadMax          (1         ).as(Integer             ) ] :Optional  :pthread: max\n");
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
