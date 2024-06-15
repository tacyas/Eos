#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]1           In1                 (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input\n");
    fprintf(stderr, "    [-i[nput]2           In2                 (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input\n");
    fprintf(stderr, "    [-i[nput]3           In3                 (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input\n");
    fprintf(stderr, "    [-o[utput]           Vx                  (NULL      ).as(outFile::mrcImage   ) \n                         Vy                  (NULL      ).as(outFile::mrcImage   ) \n                         Vz                  (NULL      ).as(outFile::mrcImage   ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-o[utput]F          OutFx               (NULL      ).as(outFile::mrcImage   ) \n                         OutFy               (NULL      ).as(outFile::mrcImage   ) \n                         OutFz               (NULL      ).as(outFile::mrcImage   ) \n                         OutDi               (NULL      ).as(outFile::mrcImage   ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-o[utput]Size       Size                (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output:Chimera\n");
    fprintf(stderr, "    [-o[utput]COMMAND    OutCOMMAND          (NULL      ).as(outFile::ASCII      ) ] :Optional  :Output:Chimera\n");
    fprintf(stderr, "    [-o[utput]BILD       OutBILD             (NULL      ).as(outFile::ASCII      ) ] :Optional  :Output:Chimera\n");
    fprintf(stderr, "    [-b[ack]g[round]     BG                  (3000      ).as(Real                ) ] :Optional  :BG\n");
    fprintf(stderr, "    [-bildThresLow       BildThresLow        (0.0       ).as(Real                ) ] :Optional  :bildThresLow\n");
    fprintf(stderr, "    [-bildThresHigh      BildThresHigh       (1.0       ).as(Real                ) ] :Optional  :bildThresHigh\n");
    fprintf(stderr, "    [-bildRangeLow       BildRangeLow        (0.0       ).as(Real                ) ] :Optional  :bildRangeLow\n");
    fprintf(stderr, "    [-bildRangeHigh      BildRangeHigh       (1.0       ).as(Real                ) ] :Optional  :bildRangeHigh\n");
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
