#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-I[nputFileList]    In                  (NULL      ).as(inFileListNoOpen    ) ] :Essential :InputDataFileList\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFileNoOpen       ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-dt[heta]           dtheta              (1         ).as(Real                ) ] :Optional  :dtheta\n");
    fprintf(stderr, "    [-dp[si]             dpsi                (1         ).as(Real                ) ] :Optional  :dpsi\n");
    fprintf(stderr, "    [-m[odeof]s[election]ms                  (0         ).as(Integer             ) ] :Optional  :modeofselection\n");
    fprintf(stderr, "    [-i[nitial]r[andom]d[ata]ird                 (1         ).as(Integer             ) ] :Optional  :InitialRandomData\n");
    fprintf(stderr, "    [-M[ax]C[ount]       MC                  (100       ).as(Integer             ) ] :Optional  :MaxCount\n");
    fprintf(stderr, "    [-F[ileName]H[eader] FileNameHeader      (EulerAngle).as(String              ) ] :Optional  :FileNameHeader\n");
    fprintf(stderr, "    [-m[odeof]i[nitial]d[ada]mid                 (0         ).as(Integer             ) ] :Optional  :modeofinitialdata\n");
    fprintf(stderr, "    [-i[nputFile]i[nitial]d[ata]InInitial           (NULL      ).as(inFile              ) ] :Optional  :InputDataFileOfInitialData\n");
    fprintf(stderr, "    [-m[odeof]s[tart]p[oint]msp                 (0         ).as(Integer             ) ] :Optional  :mode of start point\n");
    fprintf(stderr, "    [-m[odeof]a[ngular]a[rea]maa                 (0         ).as(Integer             ) ] :Optional  :mode of angular area\n");
    fprintf(stderr, "    [-p[revious]dt[heta] pdtheta             (0         ).as(Integer             ) ] :Optional  :previous dtheta\n");
    fprintf(stderr, "    [-p[revious]dp[si]   pdpsi               (0         ).as(Integer             ) ] :Optional  :previous dpsi\n");
    fprintf(stderr, "    [-m[ode]L[calculation]modeL               (0         ).as(Integer             ) ] :Optional  :Mode of L calculation\n");
    fprintf(stderr, "    [-m[ode]T[hreshold]A[ngularweight]modeTA              (0         ).as(Integer             ) ] :Optional  :Mode of Threshold of AngularWeight\n");
    fprintf(stderr, "    [-m[ode]c[alculation]a[rea]modeCA              (0         ).as(Integer             ) ] :Optional  :mode of Lvalue of calculation area\n");
    fprintf(stderr, "    [-t[hreshold]c[alculation]a[rea]TCA                 (0         ).as(Real                ) ] :Optional  :Threshold of Lvalue of calculation area\n");
    fprintf(stderr, "    [-m[ode]f[ix]        modeF               (0         ).as(Integer             ) ] :Optional  :mode of fix\n");
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
