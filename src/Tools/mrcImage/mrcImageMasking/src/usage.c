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
    fprintf(stderr, "    [-nx                 nx                  (0         ).as(Real                ) ] :Optional  :[pix] Default:in.HeaderN.x\n");
    fprintf(stderr, "    [-ny                 ny                  (0         ).as(Real                ) ] :Optional  :[pix]  Default:in.HeaderN.y\n");
    fprintf(stderr, "    [-nz                 nz                  (0         ).as(Real                ) ] :Optional  :[pix] Default:in.HeaderN.z\n");
    fprintf(stderr, "    [-cx                 cx                  (0         ).as(Real                ) ] :Optional  :[pix] Default:Center of image\n");
    fprintf(stderr, "    [-cy                 cy                  (0         ).as(Real                ) ] :Optional  :[pix] Default:Center of image\n");
    fprintf(stderr, "    [-cz                 cz                  (0         ).as(Real                ) ] :Optional  :[pix] Default:Center of image\n");
    fprintf(stderr, "    [-Rot[ation]         Euler               (0         ).as(String              ) \n                         Rot1                (0         ).as(Real                ) \n                         Rot2                (0         ).as(Real                ) \n                         Rot3                (0         ).as(Real                ) ] :Optional  :Masking Area Rotation Default: ZONS 0 0 0\n");
    fprintf(stderr, "    [-Shape              Shape               (0         ).as(Integer             ) ] :Optional  :Default:Sphere\n");
    fprintf(stderr, "    [-Soft[Edge]         Soft                (0         ).as(Integer             ) ] :Optional  :Default:\n");
    fprintf(stderr, "    [-SoftWidth          SoftWidth           (0.0       ).as(Real                ) ] :Optional  :[pix] Default:\n");
    fprintf(stderr, "    [-Normalize          Normalize           (0         ).as(Integer             ) ] :Optional  :Default:No Op\n");
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
