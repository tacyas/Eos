#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-I[nput array of file]In                  (stdin     ).as(inFileListNoOpen    ) ] :Essential :InputDataFiles\n");
    fprintf(stderr, "    [-Iter[ation]                                                                  ] :Optional  :IterationFlag\n");
    fprintf(stderr, "    [-M[olecularWeight]  MolecularWeight     (1.0       ).as(Real                ) ] :Optional  :MolecularWeight (for iteration only)\n");
    fprintf(stderr, "    [-n[Molecule]        nMolecule           (1.0       ).as(Real                ) ] :Optional  :NumberOfMolecule (for iteration only)\n");
    fprintf(stderr, "    [-Boxel              Boxel               (0         ).as(Integer             ) ] :Optional  :Final volume for iteration uning boxel unit.\n");
    fprintf(stderr, "    [-d[ensty]           Density             (1.35      ).as(Real                ) ] :Optional  :Density (for iteration only)\n");
    fprintf(stderr, "    [-I[nverse]                                                                    ] :Optional  :Inverse (for iteration only)\n");
    fprintf(stderr, "    [-Abs[olute]                                                                   ] :Optional  :AbsoluteFlag\n");
    fprintf(stderr, "    [-Th[reshold]        Th                  (0.0       ).as(Real                ) ] :Optional  :Threshold for calculation. (for iteration only) \n");
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
