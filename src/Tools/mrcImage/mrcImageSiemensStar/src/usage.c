#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile::ASCII      ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-N[umber]           Nx                  (256       ).as(Integer             ) \n                         Ny                  (256       ).as(Integer             ) ] :Optional  :Number[pixel]\n");
    fprintf(stderr, "    [-R[adius]           R                   (64        ).as(Integer             ) ] :Optional  :Radius[pixel]\n");
    fprintf(stderr, "    [-n[umber]           nRadial             (18        ).as(Integer             ) ] :Optional  :nOfRadial\n");
    fprintf(stderr, "    [-delta              Delta               (1.72      ).as(Real                ) ] :Optional  :Delta[A]\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-Shape              Shape               (0         ).as(Integer             ) ] :Optional  :Mode\n");
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
