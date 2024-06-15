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
    fprintf(stderr, "    [-dr                 dr                  (1         ).as(Real                ) ] :Optional  :Delta r of outputfile[A].\n");
    fprintf(stderr, "    [-dtheta             dtheta              (1         ).as(Real                ) ] :Optional  :Delta theta of outputfile.[degree]\n");
    fprintf(stderr, "    [-dphi               dphi                (1         ).as(Real                ) ] :Optional  :Delta phi of outputfile.[degree]\n");
    fprintf(stderr, "    [-zaxis              zx                  (0         ).as(Real                ) \n                         zy                  (0         ).as(Real                ) \n                         zz                  (1         ).as(Real                ) ] :Optional  :vector of z-axis\n");
    fprintf(stderr, "    [-xaxis              xx                  (1         ).as(Real                ) \n                         xy                  (0         ).as(Real                ) \n                         xz                  (0         ).as(Real                ) ] :Optional  :vector of x-axis\n");
    fprintf(stderr, "    [-centre             cx                  (0         ).as(Real                ) \n                         cy                  (0         ).as(Real                ) \n                         cz                  (0         ).as(Real                ) ] :Optional  :centre of image\n");
    fprintf(stderr, "    [-rweight                                                                      ] :Optional  :r-weighted\n");
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
