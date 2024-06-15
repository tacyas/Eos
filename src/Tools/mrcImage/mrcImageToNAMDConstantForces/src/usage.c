#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input:MRC\n");
    fprintf(stderr, "    [-ip[db]             InPDB               (NULL      ).as(inFile              ) ] :Essential :Input:PDB\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output: PDB with Constant Force\n");
    fprintf(stderr, "    [-w[eight]           Weight              (1.0       ).as(Real                ) ] :Optional  :Input: Weight for Constant Force\n");
    fprintf(stderr, "    [-s[calingFactor]    ScalingFactor       (1.0       ).as(Real                ) ] :Optional  :Input: Scaling Factor for Constant Force\n");
    fprintf(stderr, "    [-C[ontour]          Contour             (0.0       ).as(Real                ) ] :Optional  :Input: Contour[if density>Contour, force=0]\n");
    fprintf(stderr, "    [-R[otatemode]       Rotate              (0         ).as(Integer             ) ] :Optional  :Input: RotateMode\n");
    fprintf(stderr, "    [-RW[eight]          RWeight             (0.1       ).as(Real                ) ] :Optional  :Input: RotateWeight\n");
    fprintf(stderr, "    [-S[eed]             Seed                (0.0       ).as(Real                ) ] :Optional  :Input: Seed\n");
    fprintf(stderr, "    [-nowat[er]                                                                    ] :Optional  :No force for WAT (water residue) \n");
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
