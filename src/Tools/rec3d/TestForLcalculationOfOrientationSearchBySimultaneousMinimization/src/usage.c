#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-I[nputFileList]    In                  (NULL      ).as(inFileListNoOpen    ) ] :Essential :InputDataFileList\n");
    fprintf(stderr, "    [-i[nput]i[nitial]d[ata]iid                 (NULL      ).as(inFile              ) ] :Essential :InputInitialDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-m[ode]2            mode2               (0         ).as(Integer             ) ] :Optional  :Mode2\n");
    fprintf(stderr, "    [-dt[heta]           dtheta              (0         ).as(Integer             ) ] :Optional  :dtheta\n");
    fprintf(stderr, "    [-dp[si]             dpsi                (0         ).as(Integer             ) ] :Optional  :dpsi\n");
    fprintf(stderr, "    [-e[rror]p[oint]     ep                  (0         ).as(Integer             ) ] :Optional  :ErrorPoint\n");
    fprintf(stderr, "    [-m[ode]L[calculation]modeL               (0         ).as(Integer             ) ] :Optional  :Mode of L calculation\n");
    fprintf(stderr, "    [-m[ode]T[hreshold]A[ngularweight]modeTA              (0         ).as(Integer             ) ] :Optional  :Mode of threshold of Angular weight\n");
    fprintf(stderr, "    [-L[ogFile]          Log                 (stdout    ).as(outFile             ) ] :Optional  :LogFileName\n");
    fprintf(stderr, "    [-L[ogFile]2         Log2                (stdout    ).as(outFile             ) ] :Optional  :LogFileName2 : phi theta psi\n");
    fprintf(stderr, "    [-m[rcImage]2[D]     m2                  (NULL      ).as(outFile             ) ] :Optional  :mrcImage 2D name\n");
    fprintf(stderr, "    [-m[rcImage]3[D]     m3                  (NULL      ).as(outFile             ) ] :Optional  :mrcImage 3D name\n");
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
