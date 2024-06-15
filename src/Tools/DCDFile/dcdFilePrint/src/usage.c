#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: DCD\n");
    fprintf(stderr, "    [-i[nput]p[db]       InPDB               (NULL      ).as(inFile              ) ] :Optional  :Input: PDB\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output: ASCII\n");
    fprintf(stderr, "    [-o[utput]p[db]      OutPDB              (NULL      ).as(outFile             ) ] :Optional  :Output: PDB\n");
    fprintf(stderr, "    [-r[ange]            rStart              (10        ).as(Integer             ) \n                         rEnd                (100       ).as(Integer             ) \n                         rDelta              (10        ).as(Integer             ) ] :Optional  :Input: Start End Delta\n");
    fprintf(stderr, "    [-s[tart]            Start               (10        ).as(Integer             ) ] :Optional  :Input: Start\n");
    fprintf(stderr, "    [-e[nd]              End                 (100       ).as(Integer             ) ] :Optional  :Input: End\n");
    fprintf(stderr, "    [-d[elta]            Delta               (10        ).as(Integer             ) ] :Optional  :Input: Delta(Interval)\n");
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