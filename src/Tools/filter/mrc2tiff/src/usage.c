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
    fprintf(stderr, "    [-H[igh]             High                (0         ).as(Real                ) ] :Optional  :HighThreshold\n");
    fprintf(stderr, "    [-L[ow]              Low                 (0         ).as(Real                ) ] :Optional  :LowThreshold\n");
    fprintf(stderr, "    [-I[nverse]                                                                    ] :Optional  :Inverse(Black is white)\n");
    fprintf(stderr, "    [-raw                                                                          ] :Optional  :raw\n");
    fprintf(stderr, "    [-offset             Offset              (0         ).as(Real                ) ] :Optional  :raw\n");
    fprintf(stderr, "    [-Z                  Z                   (0         ).as(Integer             ) ] :Optional  :Each: 0<=, SerialSection:-1\n");
    fprintf(stderr, "    [-r[esolution]       Resolution          (1.0       ).as(Real                ) ] :Optional  :[A]\n");
    fprintf(stderr, "    [-r[esolution]3      ResolutionX         (1.0       ).as(Real                ) \n                         ResolutionY         (1.0       ).as(Real                ) \n                         ResolutionZ         (1.0       ).as(Real                ) ] :Optional  :[A]\n");
    fprintf(stderr, "    [-e[xtension]        format              (%%s.%%04d ).as(String              ) ] :Optional  :SerialSectionFormat\n");
    fprintf(stderr, "    [-color              colorMode           (0         ).as(Integer             ) ] :Optional  :Color\n");
    fprintf(stderr, "    [-colorRange         colorRangeMin       (0         ).as(Real                ) \n                         colorRangeMax       (100       ).as(Real                ) ] :Optional  :ColorRange\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-M[ode]             Mode                (0         ).as(Integer             ) ] :Optional  :Mode: 0:char 1:short 2:float 6:unsigned short\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode: \n\t\t\t0 (8bits), 1(16bits), 2(float)\n\t\t\t\n");
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
