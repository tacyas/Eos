#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile::mrcImage   ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-r[eference]        Ref                 (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input: Reference Header\n");
    fprintf(stderr, "    [-Nx[Number of x]    Nx                  (0         ).as(Integer             ) ] :Optional  :Nx:Default Nx of inputfile\n");
    fprintf(stderr, "    [-Ny[Number of y]    Ny                  (0         ).as(Integer             ) ] :Optional  :Ny:Default Ny of inputfile\n");
    fprintf(stderr, "    [-Nz[Number of z]    Nz                  (0         ).as(Integer             ) ] :Optional  :Nz:Default Nz of inputfile\n");
    fprintf(stderr, "    [-v[alue]            Value               (0.0       ).as(Real                ) ] :Optional  :Value of pixel\n");
    fprintf(stderr, "    [-d[elta]            d                   (0.0       ).as(Real                ) ] :Optional  :Pixel size\n");
    fprintf(stderr, "    [-M[ode]             Mode                (2         ).as(Integer             ) ] :Optional  :ImageMode: 0 char 1 short 2 Float\n");
    fprintf(stderr, "    [-Def[ault]                                                                    ] :Optional  :DefaultFixedValueSet\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile::ASCII       ) ] :Optional  :ConfigurationFile\n");
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
