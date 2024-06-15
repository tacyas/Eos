#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (stdin     ).as(inFile::mrcImage    ) ] :Essential :Input:2D\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile::mrcImage   ) ] :Essential :Output:2D\n");
    fprintf(stderr, "    [-ctf                CTF                 (stdin     ).as(inFile::ASCII       ) ] :Optional  :Input:ctfInfo\n");
    fprintf(stderr, "    [-kV                 kV                  (200       ).as(Real                ) ] :Optional  :AccVol[kV]\n");
    fprintf(stderr, "    [-Cs                 Cs                  (2.1       ).as(Real                ) ] :Optional  :Cs[mm]\n");
    fprintf(stderr, "    [-df                 Defocus             (27000     ).as(Real                ) ] :Optional  :Defocus [A]:under(+)\n");
    fprintf(stderr, "    [-A                  AoverP              (0.0       ).as(Real                ) ] :Optional  :AmplitudeContrast/PhaseContrast\n");
    fprintf(stderr, "    [-Ain                Ain                 (0.0       ).as(Real                ) ] :Optional  :IlluminationAperture[mrad]\n");
    fprintf(stderr, "    [-white              WhiteNoise          (1.0       ).as(Real                ) ] :Optional  :WhiteNoise(N/S)\n");
    fprintf(stderr, "    [-SinWin             SinWinRmin          (0.1       ).as(Real                ) \n                         SinWinRmax          (1.0       ).as(Real                ) ] :Optional  :Windowing by sine function from Rmin[A] to Rmax[A]\n");
    fprintf(stderr, "    [-ctfMode            ctfMode             (0         ).as(Integer             ) ] :Optional  :CTFMode\n");
    fprintf(stderr, "    [-Astig[matism]      dfMin               (0         ).as(Real                ) \n                         dfMax               (0         ).as(Real                ) \n                         asAxis              (0         ).as(Real                ) ] :Optional  :With Atigmatism\n");
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
