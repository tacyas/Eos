#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i                  r                   (1.0       ).as(Real                ) \n                         phi                 (90.0      ).as(Real                ) \n                         theta               (0.0       ).as(Real                ) ] :Optional  :input: coord\n");
    fprintf(stderr, "    [-o                  Out                 (stdout    ).as(outFile             ) ] :Optional  :output: coord\n");
    fprintf(stderr, "    [-centre             cx                  (0.0       ).as(Real                ) \n                         cy                  (0.0       ).as(Real                ) \n                         cz                  (0.0       ).as(Real                ) ] :Optional  :Centre\n");
    fprintf(stderr, "    [-xaxis              xx                  (1.0       ).as(Real                ) \n                         xy                  (0.0       ).as(Real                ) \n                         xz                  (0.0       ).as(Real                ) ] :Optional  :x-axis\n");
    fprintf(stderr, "    [-zaxis              zx                  (0.0       ).as(Real                ) \n                         zy                  (0.0       ).as(Real                ) \n                         zz                  (1.0       ).as(Real                ) ] :Optional  :z-axis\n");
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
