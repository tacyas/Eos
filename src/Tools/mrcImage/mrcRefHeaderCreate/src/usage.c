#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-p[osition]         iP                  (0         ).as(Real                ) \n                         iW                  (0         ).as(Real                ) \n                         iA                  (0         ).as(Real                ) ] :Optional  :Position of Center of model creation. Phi(degree) ,Omega(degree) ,Alpha(degree) \n:Omega and Alpha range must be around 0 or 180. \n");
    fprintf(stderr, "    [-w[idth]            Wp                  (360       ).as(Real                ) \n                         Ww                  (10        ).as(Real                ) \n                         Wa                  (10        ).as(Real                ) ] :Optional  :Width of Phi(degree,plus minus) ,Omega(degree,plus minus) ,Alpha(degree,plus minus) \n");
    fprintf(stderr, "    [-d[elta]            Dp                  (5         ).as(Real                ) \n                         Dw                  (5         ).as(Real                ) \n                         Da                  (5         ).as(Real                ) ] :Optional  :Interval of model creation(degree) Phi(around Z axis),Omega(Y axis),Alpha(X axis)\n");
    fprintf(stderr, "    [-s[tart]y           Sy                  (0         ).as(Integer             ) ] :Optional  :Start y: For mode 1 only\n");
    fprintf(stderr, "    [-e[end]y            Ey                  (0         ).as(Integer             ) ] :Optional  :End y: For mode 1 only. Default is Ny-1\n");
    fprintf(stderr, "    [-refsize            Refsize             (0         ).as(Integer             ) ] :Optional  :Size of reference data.\n");
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
