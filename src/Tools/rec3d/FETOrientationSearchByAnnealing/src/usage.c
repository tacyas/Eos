#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nputMS]          InMS                (NULL      ).as(inFile              ) ] :Essential :InputMapSet\n");
    fprintf(stderr, "    [-i[nput]F[ile]      InFL                (NULL      ).as(inFile              ) ] :Optional  :InputFETDataFileList\n");
    fprintf(stderr, "    [-i[nput]M[aps]      InML                (NULL      ).as(inFile              ) ] :Optional  :InputMapDataFileList\n");
    fprintf(stderr, "    [-T[emprature]       ITemp               (300.0     ).as(Real                ) ] :Optional  :InitialTemprature\n");
    fprintf(stderr, "    [-a[nnealing]s[chedule]1AS1                 (10        ).as(Integer             ) ] :Optional  :Repeatas1TimesInSameTemp\n");
    fprintf(stderr, "    [-a[nnealing]s[chedule]2AS2                 (0.9       ).as(Real                ) ] :Optional  :TempratureDecreaseConstant\n");
    fprintf(stderr, "    [-a[nnealing]s[chedule]3AS3                 (10        ).as(Integer             ) ] :Optional  :Repeatas3Times\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
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
