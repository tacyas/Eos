#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (stdin     ).as(inFileList          ) ] :Essential :Input: filename ...\n");
    fprintf(stderr, "    [-info2              CTF                 (stdin     ).as(inFileList          ) ] :Optional  :InputFileList: the same order as the input: ctfinfo from Display2/ctfDisplay\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Essential :OutputDataFile(average file)\n");
    fprintf(stderr, "    [-f[ft]              fftOut              (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile(averaged fft file)\n");
    fprintf(stderr, "    [-W[hiteNoise]       WhiteNoise          (1.0       ).as(Real                ) ] :Optional  :\n");
    fprintf(stderr, "    [-W[hiteNoise]R[aising]WhiteNoiseRaising   (1.0       ).as(Real                ) ] :Optional  :Weight:W*exp(WR*R)\n");
    fprintf(stderr, "    [-maxW[hiteNoise]R[aising]MaxWhiteNoise       (1.0       ).as(Real                ) ] :Optional  :max(W*exp(WR*R),maxWhiteNoise)\n");
    fprintf(stderr, "    [-Ndep[endent]W[hiteNoise]R[aising]NdependentWhiteNoise(1         ).as(Integer             ) ] :Optional  :W*exp(WR*R)/sqrt(N)\n");
    fprintf(stderr, "    [-SinWin             SinWinRmin          (0.1       ).as(Real                ) \n                         SinWinRmax          (1.0       ).as(Real                ) ] :Optional  :Windowing by sine function from Rmin[/A] to Rmax[/A]\n");
    fprintf(stderr, "    [-MaxIter[ation]     MaxIter             (10        ).as(Integer             ) ] :Optional  :Max Iteration\n");
    fprintf(stderr, "    [-ctfMode            CTFMode             (1         ).as(Integer             ) ] :Optional  :CTFMode: refer to mrcImageCTFObservation\n");
    fprintf(stderr, "    [-solventMode        solventMode         (0         ).as(Real                ) ] :Optional  :If solvent flatterning is used, NEED\n");
    fprintf(stderr, "    [-solventSTD         solventSTD          (-1.0      ).as(Real                ) ] :Optional  :If solvent flatterning is used as mode=1, NEED \n");
    fprintf(stderr, "    [-log[file]          Log                 (stderr    ).as(outFile             ) ] :Optional  :Log File Name\n");
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
