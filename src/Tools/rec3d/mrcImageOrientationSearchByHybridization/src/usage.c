#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-I[nputFileLiest]   In                  (NULL      ).as(inFileListNoOpen    ) ] :Essential :InputDataFileList\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(String              ) ] :Essential :OutputDataFileHeader\n");
    fprintf(stderr, "    [-e[xtension]        extension           (NULL      ).as(String              ) ] :Essential :OutputDataFileExtension\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-i[ncrease]r[ate]   ir                  (1         ).as(Integer             ) ] :Optional  :IncreaseRate\n");
    fprintf(stderr, "    [-h[ybridization]p[oint]n[umber]hpn                 (1         ).as(Integer             ) ] :Optional  :HybridizationPointNumber\n");
    fprintf(stderr, "    [-m[ode]s[election]  ms                  (0         ).as(Integer             ) ] :Optional  :ModeOfSelection\n");
    fprintf(stderr, "    [-i[nitial]r[andom]d[ata]ird                 (0         ).as(Integer             ) ] :Optional  :InitialRandomData\n");
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
