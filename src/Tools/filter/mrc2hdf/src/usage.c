#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcInfo     ) ] :Optional  :Input\n");
    fprintf(stderr, "    [-I[nput]            InList              (NULL      ).as(inFileList::mrcInfo ) ] :Optional  :Input:FileList\n");
    fprintf(stderr, "    [-I[nput]2           InList2             (NULL      ).as(inFileList::mrcInfo ) ] :Optional  :Input:FileList\n");
    fprintf(stderr, "    [-I[nput]color       IR                  (1.0       ).as(Real                ) \n                         IG                  (0.0       ).as(Real                ) \n                         IB                  (0.0       ).as(Real                ) \n                         IA                  (1.0       ).as(Real                ) ] :Optional  :RGBA\n");
    fprintf(stderr, "    [-I[nput]2color      I2R                 (0.0       ).as(Real                ) \n                         I2G                 (1.0       ).as(Real                ) \n                         I2B                 (0.0       ).as(Real                ) \n                         I2A                 (1.0       ).as(Real                ) ] :Optional  :RGBA\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-nres[olution]      nResolution         (1         ).as(Integer             ) ] :Optional  :Pyramidal Resolution\n");
    fprintf(stderr, "    [-M[ode]             hdf5mode            (1         ).as(Integer             ) ] :Optional  :Mode:0 hdf5 1 imaris\n");
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
