#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-n[Molecule]        nMolecule           (1.0       ).as(Real                ) ] :Optional  :NumberOfMolecule\n");
    fprintf(stderr, "    [-M[olecularWeight]  MolecularWeight     (1.0       ).as(Real                ) ] :Optional  :MolecularWeight\n");
    fprintf(stderr, "    [-d[ensty]           Density             (1.35      ).as(Real                ) ] :Optional  :Density\n");
    fprintf(stderr, "    [-D[elta]            Delta               (5.0       ).as(Real                ) ] :Optional  :Delta[A]\n");
    fprintf(stderr, "    [-R[ange]            MinVol              (0.0       ).as(Real                ) \n                         MaxVol              (200.0     ).as(Real                ) \n                         DeltaVol            (10.0      ).as(Real                ) ] :Optional  :vol%\n");
    fprintf(stderr, "    [-I[nverse]                                                                    ] :Optional  :Inverse\n");
    fprintf(stderr, "    [-format             Format              (ContourLevel(%%3g): %%g %%lu).as(StringAll           ) ] :Optional  :Format\n");
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
