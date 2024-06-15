#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Optional  :In: MRC\n");
    fprintf(stderr, "    [-I[nput]            InList              (NULL      ).as(inFileList          ) ] :Optional  :In: MRC\n");
    fprintf(stderr, "    [-r[ef]              Ref                 (NULL      ).as(inFile              ) ] :Essential :Ref: MRC\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output: Correlation\n");
    fprintf(stderr, "    [-O[utput]           Out2                (stdout    ).as(outFile             ) ] :Optional  :Output: Estimated\n");
    fprintf(stderr, "    [-range              thetaMin            (-90       ).as(Real                ) \n                         thetaMax            (+90       ).as(Real                ) \n                         thetaDelta          (1         ).as(Real                ) ] :Optional  :Search Range [degree]\n");
    fprintf(stderr, "    [-w[idth]            Width               (0.5       ).as(Real                ) ] :Optional  :Projection Range[MIn(Nx,Ny)*Width] around centre\n");
    fprintf(stderr, "    [-M[ode]             Mode                (2         ).as(Integer             ) ] :Optional  :Interpolation Mode\n");
    fprintf(stderr, "    [-C[orrelation]M[ode]CorrelationMode     (17        ).as(Integer             ) ] :Optional  :Correlation Mode\n");
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
