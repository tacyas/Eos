#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-I[nput]            In2                 (NULL      ).as(inFileList          ) ] :Essential :InputDataFileList\n");
    fprintf(stderr, "    [-I[nput]b[efore]    InBefore            (NULL      ).as(inFileList          ) ] :Optional  :InputDataFileListBefore\n");
    fprintf(stderr, "    [-i[nput]b[efore]    inbefore            (NULL      ).as(inFile              ) ] :Optional  :InputDataFileBeforeData: mrcImageRadon3D\n");
    fprintf(stderr, "    [-i[nput]w[eight]b[efore]inWbefore           (NULL      ).as(inFile              ) ] :Optional  :InputWeightDataFileBeforeData: mrcImageRadon3D\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile: radon3D\n");
    fprintf(stderr, "    [-o[utput]w[eight]   OutW                (NULL      ).as(outFile             ) ] :Essential :OutputDataFile: weight\n");
    fprintf(stderr, "    [-dp                 dp                  (2.0       ).as(Real                ) ] :Essential :Input: deltaP\n");
    fprintf(stderr, "    [-dtheta             dtheta              (1         ).as(Real                ) ] :Essential :Input: deltaTheta\n");
    fprintf(stderr, "    [-dphi               dphi                (1         ).as(Real                ) ] :Essential :Input: deltaPhi\n");
    fprintf(stderr, "    [-T[hreshold]        T                   (1.0       ).as(Real                ) ] :Optional  :Threshold\n");
    fprintf(stderr, "    [-InterpolationMode  InterpolationMode   (0         ).as(Integer             ) ] :Optional  :InterpolationMode\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Radon2Dto3D Intepolation Mode\n");
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
