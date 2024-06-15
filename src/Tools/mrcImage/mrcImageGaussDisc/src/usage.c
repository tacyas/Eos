#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-sigmax             sigmax              (10        ).as(Real                ) ] :Optional  :sigmax[A]\n");
    fprintf(stderr, "    [-sigmay             sigmay              (10        ).as(Real                ) ] :Optional  :sigmay[A]\n");
    fprintf(stderr, "    [-sigma_range        sigma_range         (3         ).as(Real                ) ] :Optional  :sigma\n");
    fprintf(stderr, "    [-weight             weight              (10        ).as(Real                ) ] :Optional  :weight\n");
    fprintf(stderr, "    [-size               size                (5         ).as(Real                ) ] :Optional  :Pixel Size[A]\n");
    fprintf(stderr, "    [-W[idth]            Width               (0         ).as(Real                ) ] :Optional  :Image Width[A]\n");
    fprintf(stderr, "    [-H[eight]           Height              (0         ).as(Real                ) ] :Optional  :Image Height[A]\n");
    fprintf(stderr, "    [-cx                 centrex             (0         ).as(Real                ) ] :Optional  :x: Centre[A]\n");
    fprintf(stderr, "    [-cy                 centrey             (0         ).as(Real                ) ] :Optional  :y: Centre[A]\n");
    fprintf(stderr, "    [-a[ngle]            Angle               (0         ).as(Real                ) ] :Optional  :Angle: [degree]\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (2         ).as(Integer             ) ] :Optional  :Mode\n");
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
