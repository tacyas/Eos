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
    fprintf(stderr, "    [-ZXY                ZXYrotx             (0.0       ).as(Real                ) \n                         ZXYroty             (0.0       ).as(Real                ) \n                         ZXYrotz             (0.0       ).as(Real                ) ] :Optional  :ZXY*pdb: rotz(rotz)rotx(rotx)roty(roty) \n");
    fprintf(stderr, "    [-ZYX                ZYXrotx             (0.0       ).as(Real                ) \n                         ZYXroty             (0.0       ).as(Real                ) \n                         ZYXrotz             (0.0       ).as(Real                ) ] :Optional  :ZYX*pdb: rotz(rotz)roty(roty)rotx(rotx) \n");
    fprintf(stderr, "    [-YXZ                YXZrotx             (0.0       ).as(Real                ) \n                         YXZroty             (0.0       ).as(Real                ) \n                         YXZrotz             (0.0       ).as(Real                ) ] :Optional  :YXZ*pdb: roty(roty)rotx(rotx)rotz(rotz) \n");
    fprintf(stderr, "    [-XYZ                XYZrotx             (0.0       ).as(Real                ) \n                         XYZroty             (0.0       ).as(Real                ) \n                         XYZrotz             (0.0       ).as(Real                ) ] :Optional  :XYZ*pdb: rotx(rotx)roty(roty)rotz(rotz) \n");
    fprintf(stderr, "    [-E[uler]A[ngle]     RotMode             (YOYS      ).as(String              ) \n                         Rot1                (0.0       ).as(Real                ) \n                         Rot2                (0.0       ).as(Real                ) \n                         Rot3                (0.0       ).as(Real                ) ] :Optional  :EA*pdb: EA=rot(rot3)rot(rot2)rot(rot1) \n");
    fprintf(stderr, "    [-cuda               cudaDeviceID        (0         ).as(Integer             ) ] :Optional  :UseCuda\n");
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
