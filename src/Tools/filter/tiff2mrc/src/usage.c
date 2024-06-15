#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            inFile              (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           outFile             (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-r[esolution]       Resolution          (1.0       ).as(Real                ) ] :Optional  :Resolution[A]\n");
    fprintf(stderr, "    [-r[esolution]3      ResolutionX         (1.0       ).as(Real                ) \n                         ResolutionY         (1.0       ).as(Real                ) \n                         ResolutionZ         (1.0       ).as(Real                ) ] :Optional  :Resolution[A]\n");
    fprintf(stderr, "    [-t[ime]             time                (1.0       ).as(Real                ) ] :Optional  :x OptimalTime\n");
    fprintf(stderr, "    [-d[irnum]           dirnum              (-1        ).as(Integer             ) ] :Optional  :tiffDirectoryNumber\n");
    fprintf(stderr, "    [-I[nverse]                                                                    ] :Optional  :Black<->White\n");
    fprintf(stderr, "    [-Signed                                                                       ] :Optional  :Original image is Signed or Not: Default unsigned\n");
    fprintf(stderr, "    [-Offset             Offset              (0.0       ).as(Real                ) ] :Optional  :OffsetValue\n");
    fprintf(stderr, "    [-Max                Max                 (16        ).as(Real                ) ] :Optional  :MaxValue:2^Max\n");
    fprintf(stderr, "    [-Min                Min                 (1         ).as(Real                ) ] :Optional  :MinValue:2^Min: without 0\n");
    fprintf(stderr, "    [-realMin            realMin             (0.0       ).as(Real                ) ] :Optional  :Real MinValue\n");
    fprintf(stderr, "    [-realMax            realMax             (0.0       ).as(Real                ) ] :Optional  :Real MaxValue\n");
    fprintf(stderr, "    [-realMaxBit         realMaxBit          (14        ).as(Real                ) ] :Optional  :Real MaxValue Bit\n");
    fprintf(stderr, "    [-sin                sinFile             (NULL      ).as(inFile              ) ] :Optional  :sin file from Zeiss\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-S[hrink]           Shrink              (8         ).as(Integer             ) ] :Optional  :ShrinkMode\n");
    fprintf(stderr, "    [-M[ode]             Mode                (0         ).as(Integer             ) ] :Optional  :Mode: mrcMode: Def: if -m 0, -M 0. if -m 1 -M 2\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode: 0 (Direct), 1(Log10(65535/data))\n");
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
