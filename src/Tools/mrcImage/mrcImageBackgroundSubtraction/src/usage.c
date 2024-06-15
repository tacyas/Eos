#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input[Array]\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output[Array]\n");
    fprintf(stderr, "    [-w[idth]x           widthX              (1         ).as(Real                ) ] :Optional  :WindowX[piX]\n");
    fprintf(stderr, "    [-w[idth]y           widthY              (1         ).as(Real                ) ] :Optional  :WindowY[pix]\n");
    fprintf(stderr, "    [-w[idth]z           widthZ              (1         ).as(Real                ) ] :Optional  :WindowZ[pix]\n");
    fprintf(stderr, "    [-e[dge]x            edgeX               (1         ).as(Real                ) ] :Optional  :EdgeX[pix]\n");
    fprintf(stderr, "    [-e[dge]y            edgeY               (1         ).as(Real                ) ] :Optional  :EdgeY[pix]\n");
    fprintf(stderr, "    [-e[dge]z            edgeZ               (1         ).as(Real                ) ] :Optional  :EdgeZ[pix]\n");
    fprintf(stderr, "    [-trim               Trim                (0         ).as(Real                ) ] :Optional  :trimmedAbnormalValue[0-0.5]\n");
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
