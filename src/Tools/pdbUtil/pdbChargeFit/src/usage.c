#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]f[ixed pdb] InFix               (NULL      ).as(inFile              ) ] :Essential :InputFixedPdbFile\n");
    fprintf(stderr, "    [-i[nput]m[oved pdb] InMove              (NULL      ).as(inFile              ) ] :Essential :InputMovedPdbFile\n");
    fprintf(stderr, "    [-o[utput]           OutTxt              (NULL      ).as(outFile             ) ] :Essential :OutputTextFile\n");
    fprintf(stderr, "    [-s[ymmetry of helix(degree/A)]symmetry            (0.47096   ).as(Real                ) ] :Optional  :default: 13/28\n");
    fprintf(stderr, "    [-zmin               zmin                (-28       ).as(Real                ) ] :Optional  :minimum z\n");
    fprintf(stderr, "    [-zmax               zmax                (28        ).as(Real                ) ] :Optional  :maximum z\n");
    fprintf(stderr, "    [-zDel[ta]           zDel                (1         ).as(Real                ) ] :Optional  :delta z\n");
    fprintf(stderr, "    [-mind[istance]      mind                (1         ).as(Real                ) ] :Optional  :set atoms distance to mind\n");
    fprintf(stderr, "    [-maxd[istance]      maxd                (5         ).as(Real                ) ] :Optional  :ignore atoms distance\n");
    fprintf(stderr, "    [-a[xis coordinate]  axisX               (70        ).as(Real                ) \n                         axisY               (70        ).as(Real                ) ] :Optional  :(x, y)\n");
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
