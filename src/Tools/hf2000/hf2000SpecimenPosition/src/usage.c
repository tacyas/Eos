#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-tty                tty                 (/dev/ttyS1).as(String              ) ] :Optional  :TTY\n");
    fprintf(stderr, "    [-speed              Speed               (4800      ).as(Integer             ) ] :Optional  :Speed\n");
    fprintf(stderr, "    [-p[osition]         posX                (0.0       ).as(Real                ) \n                         posY                (0.0       ).as(Real                ) ] :Optional  :Set Position[um,um]\n");
    fprintf(stderr, "    [-I[nteractive]      Interactive         (5         ).as(Integer             ) ] :Optional  :Interactive[sec]\n");
    fprintf(stderr, "    [-S[erver]           Host                (tkyemg-pc06).as(String              ) \n                         Port                (6000      ).as(Integer             ) ] :Optional  :Host port Server[sec]\n");
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
