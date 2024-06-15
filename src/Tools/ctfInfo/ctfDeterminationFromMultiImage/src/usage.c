#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFileList          ) ] :Optional  :Input: mrcImageList\n");
    fprintf(stderr, "    [-i[nput]            In2                 (NULL      ).as(inFileList          ) ] :Optional  :Input: AngularDistributionList\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output: Result obtained by fitting procedure\n");
    fprintf(stderr, "    [-O[utput]           Out2                (.estimate ).as(String              ) ] :Optional  :Output: Estimated scattering: add this value to input filename\n");
    fprintf(stderr, "    [-Molec[ular]Env[elope]MolecEnv            (50        ).as(Real                ) ] :Optional  :Input [A]: Spread : Assign molecular envelope as Gaussian\n");
    fprintf(stderr, "    [-Molec[ular]Env[elope]2MolecEnvFile        (NULL      ).as(String              ) ] :Optional  :Input filename: Scattering Factor suggested by Table\n");
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
