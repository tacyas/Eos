#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-o[utput] F[ile]    OutF                (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-o[utput]I[nformation]OutI                (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-truePitch          truePitch           (430       ).as(Real                ) ] :Optional  :True Pitch\n");
    fprintf(stderr, "    [-PixelSize          PixelSize           (5         ).as(Real                ) ] :Optional  :Pixel Size [A]\n");
    fprintf(stderr, "    [-deltadY            deltadY             (0.5       ).as(Real                ) ] :Optional  :A range of deltadY to determine dY.\n");
    fprintf(stderr, "    [-kV                 kV                  (200       ).as(Real                ) ] :Optional  :AccVol[kV]\n");
    fprintf(stderr, "    [-Cs                 Cs                  (2.1       ).as(Real                ) ] :Optional  :Cs[mm]\n");
    fprintf(stderr, "    [-df                 Defocus             (27000     ).as(Real                ) ] :Optional  :Defocus[A]:under(+)\n");
    fprintf(stderr, "    [-A                  AoverP              (0.1       ).as(Real                ) ] :Optional  :AmplitudeContrast/PhaseContrast\n");
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