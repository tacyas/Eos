#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (stdin     ).as(inFile              ) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-i[nput] N[ame]     InN                 (stdin     ).as(String              ) ] :Optional  :InputNameInInformationFile\n");
    fprintf(stderr, "    [-i[nput] R[eference]InR                 (stdin     ).as(String              ) ] :Optional  :InputReferenceForLength\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-o[utput] I[nformation]OutI                (stdout    ).as(outFile             ) ] :Optional  :OutputInformationFile\n");
    fprintf(stderr, "    [-o[utput] I[nformation]OutI2               (stdout    ).as(outFile             ) ] :Optional  :OutputInformationFile\n");
    fprintf(stderr, "    [-o[utput] I[nformation]OutI3               (stdout    ).as(outFile             ) ] :Optional  :OutputInformationFile\n");
    fprintf(stderr, "    [-kV                 kV                  (200       ).as(Real                ) ] :Optional  :kV\n");
    fprintf(stderr, "    [-Cs                 Cs                  (2.1       ).as(Real                ) ] :Optional  :Cs[mm]\n");
    fprintf(stderr, "    [-A[mplitude contrast]AoverP              (0.05      ).as(Real                ) ] :Optional  :The ratio of amplitude contrast to phase contrast\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-ctfMode            ctfMode             (0         ).as(Integer             ) ] :Optional  :CTFMode\n");
    fprintf(stderr, "    [-truePitch          truePitch           (430       ).as(Real                ) ] :Optional  :True Pitch\n");
    fprintf(stderr, "    [-PixelSize          PixelSize           (5         ).as(Real                ) ] :Optional  :Pixel Size [A]\n");
    fprintf(stderr, "    [-deltadY            deltadY             (0.5       ).as(Real                ) ] :Optional  :A range of deltadY to determine dY.\n");
    fprintf(stderr, "    [-R[/A]              R                   (NULL      ).as(Real                ) ... ] :Variable  :ThonRing[/A]\n");
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
