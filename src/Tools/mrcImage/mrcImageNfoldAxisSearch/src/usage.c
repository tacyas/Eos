#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output: centre\n");
    fprintf(stderr, "    [-O[utput]           Out2                (stdout    ).as(outFile             ) ] :Optional  :Output: shifted Image\n");
    fprintf(stderr, "    [-res[ideu]          Res                 (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-n[Fold]            nFold               (2         ).as(Integer             ) ] :Essential :Input: nFold\n");
    fprintf(stderr, "    [-delPHI             delPHI              (1.0       ).as(Real                ) ] :Optional  :Input: delPHI[degree]\n");
    fprintf(stderr, "    [-rangex             minx                (-3        ).as(Real                ) \n                         maxx                (3         ).as(Real                ) \n                         delx                (1         ).as(Real                ) ] :Optional  :Input: range [pixel size]\n");
    fprintf(stderr, "    [-rangey             miny                (-3        ).as(Real                ) \n                         maxy                (3         ).as(Real                ) \n                         dely                (1         ).as(Real                ) ] :Optional  :Input: range [pixel size]\n");
    fprintf(stderr, "    [-rangez             minz                (0         ).as(Real                ) \n                         maxz                (0         ).as(Real                ) \n                         delz                (1         ).as(Real                ) ] :Optional  :Input: range [pixel size]\n");
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
