#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Optional  :Input DataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-t[urn]             Turn                (-13       ).as(Integer             ) ] :Essential :Tern\n");
    fprintf(stderr, "    [-u[nit]             Unit                (28        ).as(Integer             ) ] :Essential :Unit\n");
    fprintf(stderr, "    [-N[-helix]          nHelix              (1         ).as(Integer             ) ] :Optional  :Helix\n");
    fprintf(stderr, "    [-dY                 dY                  (3         ).as(Integer             ) ] :Optional  :Position of the 1st layer line: [pixel]\n");
    fprintf(stderr, "    [-truePitch          truePitch           (770       ).as(Integer             ) ] :Essential :truePitch [A]\n");
    fprintf(stderr, "    [-rMax               rMax                (50        ).as(Real                ) ] :Essential :rMax [A]\n");
    fprintf(stderr, "    [-RMax               RMax                (0.1       ).as(Real                ) ] :Optional  :RMax [/A]\n");
    fprintf(stderr, "    [-RZMax              RZMax               (0.1       ).as(Real                ) ] :Optional  :RZMax [/A]\n");
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
