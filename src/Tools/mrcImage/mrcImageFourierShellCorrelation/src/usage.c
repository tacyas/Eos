#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i1[input1]         In1                 (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input:\n");
    fprintf(stderr, "    [-i2[input2]         In2                 (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input:\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile::ASCII      ) ] :Optional  :Output:FSC\n");
    fprintf(stderr, "    [-SNR                                                                          ] :Optional  :flagSNR\n");
    fprintf(stderr, "    [-FSCfull                                                                      ] :Optional  :flagFSCfull\n");
    fprintf(stderr, "    [-Cref                                                                         ] :Optional  :flagCref\n");
    fprintf(stderr, "    [-NoiseWeighted      Brestore            (-1000     ).as(Real                ) ] :Optional  :flagNoiseWeighted: Cref*exp(-Bfactor/(4*d^2)\n");
    fprintf(stderr, "    [-d[elta]            delta               (0         ).as(Real                ) ] :Optional  :Interval of output data(1/A). Default 1/(Nx*size of pixel)\n");
    fprintf(stderr, "    [-z[position]        z                   (0         ).as(Integer             ) ] :Optional  :z position of reference file to correlate.For mode2=1 only\n");
    fprintf(stderr, "    [-L[owThreshold]     L                   (0         ).as(Real                ) ] :Optional  :Low threshold for mode +2.\n");
    fprintf(stderr, "    [-H[ighThreshold]    H                   (0         ).as(Real                ) ] :Optional  :High threshold for mode +2.\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-M[ode2]            mode2               (0         ).as(Integer             ) ] :Optional  :Mode2\n");
    fprintf(stderr, "    [-I1[nput array of file]In1Array            (stdin     ).as(inFileList          ) ] :Optional  :InputDataFiles\n");
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
