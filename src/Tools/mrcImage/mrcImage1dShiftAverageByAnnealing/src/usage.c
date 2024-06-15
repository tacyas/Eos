#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-s[ignal position]  Signal              (NULL      ).as(inFile              ) ] :Essential :File to define position of signal\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-r[ange]            range               (0         ).as(Integer             ) ] :Optional  :Search range of shift.Default:Nx\n");
    fprintf(stderr, "    [-d[elta]            delta               (1.0       ).as(Real                ) ] :Optional  :Spacing of molecule(Pixel).\n");
    fprintf(stderr, "    [-T[eperature]       temperature         (1.0       ).as(Real                ) ] :Optional  :Initial temperature.\n");
    fprintf(stderr, "    [-iter[ation]        iter                (1000      ).as(Integer             ) ] :Optional  :Number of iteration before reducing temperature.\n");
    fprintf(stderr, "    [-eps[ilon]          eps                 (0.001     ).as(Real                ) ] :Optional  :Temperature(T) reduced to (1-epsilon)T.\n");
    fprintf(stderr, "    [-tol                tol                 (1e-2      ).as(Real                ) ] :Optional  :Number to identify convergence\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-M[ode2]            mode2               (0         ).as(Integer             ) ] :Optional  :Mode2\n");
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
