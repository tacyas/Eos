#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile::ASCII      ) ] :Optional  :Output\n");
    fprintf(stderr, "    [-X[Section]         X                   (0.0       ).as(Real                ) ] :Optional  :X Section at y=X(value)\n");
    fprintf(stderr, "    [-Y[Section]         Y                   (0.0       ).as(Real                ) ] :Optional  :Y Section at y=Y(value)\n");
    fprintf(stderr, "    [-x[Projection]                                                                ] :Optional  :x Projection[OutPut ASCII FILE]\n");
    fprintf(stderr, "    [-y[Projection]                                                                ] :Optional  :y Projection[OutPut ASCII FILE]\n");
    fprintf(stderr, "    [-L[ength]                                                                     ] :Optional  :with Length[A]\n");
    fprintf(stderr, "    [-H[istgram]         H                   (256       ).as(Integer             ) ] :Optional  :Histgram: Class Number: Normalize\n");
    fprintf(stderr, "    [-H[istgram]2        H2                  (1         ).as(Real                ) ] :Optional  :Histgram2: Class Width: Integer: Normalize\n");
    fprintf(stderr, "    [-H[istgram]3        H3                  (256       ).as(Integer             ) ] :Optional  :Histgram: Class Number: Count\n");
    fprintf(stderr, "    [-H[istgram]4        H4                  (1         ).as(Real                ) ] :Optional  :Histgram2: Class Width: Integer: Count\n");
    fprintf(stderr, "    [-H[istgram]5        H5                  (1         ).as(Integer             ) ] :Optional  :Histgram5: Class Number: Count\n");
    fprintf(stderr, "    [-H[istgram]6        H6                  (1         ).as(Real                ) ] :Optional  :Histgram6: Class Width: Integer: Count\n");
    fprintf(stderr, "    [-Low                Low                 (1         ).as(Real                ) ] :Optional  :Low\n");
    fprintf(stderr, "    [-High               High                (1         ).as(Real                ) ] :Optional  :High\n");
    fprintf(stderr, "    [-thres              Thres               (0.5       ).as(Real                ) ] :Optional  :threshold(rate)\n");
    fprintf(stderr, "    [-I[nfo]                                                                       ] :Optional  :Information\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-rmax               rmax                (250       ).as(Real                ) ] :Optional  :rmax [A]\n");
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
