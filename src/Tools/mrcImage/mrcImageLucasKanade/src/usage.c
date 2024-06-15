#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            InVx                (NULL      ).as(inFile::mrcImage    ) \n                         InVy                (NULL      ).as(inFile::mrcImage    ) \n                         InVz                (NULL      ).as(inFile::mrcImage    ) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-I[nput]            InVxList            (NULL      ).as(inFileList::mrcImage) \n                         InVyList            (NULL      ).as(inFileList::mrcImage) \n                         InVzList            (NULL      ).as(inFileList::mrcImage) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-i[nput]1           In1Vx               (NULL      ).as(inFile::mrcImage    ) \n                         In1Vy               (NULL      ).as(inFile::mrcImage    ) \n                         In1Vz               (NULL      ).as(inFile::mrcImage    ) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-i[nput]2           In2Vx               (NULL      ).as(inFile::mrcImage    ) \n                         In2Vy               (NULL      ).as(inFile::mrcImage    ) \n                         In2Vz               (NULL      ).as(inFile::mrcImage    ) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-i[nput]3           In3Vx               (NULL      ).as(inFile::mrcImage    ) \n                         In3Vy               (NULL      ).as(inFile::mrcImage    ) \n                         In3Vz               (NULL      ).as(inFile::mrcImage    ) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-i[nput]4           In4Vx               (NULL      ).as(inFile::mrcImage    ) \n                         In4Vy               (NULL      ).as(inFile::mrcImage    ) \n                         In4Vz               (NULL      ).as(inFile::mrcImage    ) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           outVx               (NULL      ).as(outFile::mrcImage   ) \n                         outVy               (NULL      ).as(outFile::mrcImage   ) \n                         outVz               (NULL      ).as(outFile::mrcImage   ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-n[umber]o[f]s[tairs]NOS                 (4         ).as(Real                ) ] :Optional  :NOS\n");
    fprintf(stderr, "    [-o[utput]Size       Size                (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output:Chimera\n");
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
