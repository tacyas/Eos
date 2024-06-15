#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput] information fileOut                 (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-o[utput] Cor[relation]OutCor              (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-ref[erence array of file]ref                 (stdin     ).as(inFileListNoOpen    ) ] :Essential :InputDataFiles\n");
    fprintf(stderr, "    [-cor[relation] file namecorfilename         (stdin     ).as(inFileListNoOpen    ) ] :Optional  :InputDataFiles\n");
    fprintf(stderr, "    [-cormode            cormode             (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-ctfinfo            ctfinfo             (NULL      ).as(inFile              ) ] :Optional  :InputDataFile\n");
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
