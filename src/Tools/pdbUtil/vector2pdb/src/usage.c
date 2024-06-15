#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-v[ector]           vx                  (1         ).as(Real                ) \n                         vy                  (0         ).as(Real                ) \n                         vz                  (0         ).as(Real                ) ] :Optional  :Input: vector\n");
    fprintf(stderr, "    [-polar[vector]      phi                 (0         ).as(Real                ) \n                         theta               (0         ).as(Real                ) ] :Optional  :Input: vector[degree]\n");
    fprintf(stderr, "    [-polarz[axis]       zx                  (0         ).as(Real                ) \n                         zy                  (0         ).as(Real                ) \n                         zz                  (1         ).as(Real                ) ] :Optional  :Input: z-axis for polar\n");
    fprintf(stderr, "    [-polarx[axis]       xx                  (1         ).as(Real                ) \n                         xy                  (0         ).as(Real                ) \n                         xz                  (0         ).as(Real                ) ] :Optional  :Input: x-axis for polar\n");
    fprintf(stderr, "    [-ori[ginal]         sx                  (0         ).as(Real                ) \n                         sy                  (3         ).as(Real                ) \n                         sz                  (0         ).as(Real                ) ] :Optional  :Input: origin\n");
    fprintf(stderr, "    [-step               step                (1.6       ).as(Real                ) ] :Optional  :Input: step [A]\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output: pdbFile\n");
    fprintf(stderr, "    [-n                  n                   (20        ).as(Integer             ) ] :Optional  :Input: Number Of CA\n");
    fprintf(stderr, "    [-ID                 ID                  (A         ).as(Character           ) ] :Optional  :Input: Chain ID\n");
    fprintf(stderr, "    [-Res                Res                 (GLY       ).as(String              ) ] :Optional  :Input: Chain ID\n");
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
