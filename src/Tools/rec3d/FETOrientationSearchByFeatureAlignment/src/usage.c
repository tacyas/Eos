#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            InS                 (NULL      ).as(inFile              ) ] :Optional  :InputSinogramList\n");
    fprintf(stderr, "    [-i[nput]2           InS2                (NULL      ).as(inFile              ) ] :Optional  :InputMoreSinogramList\n");
    fprintf(stderr, "    [-I[nputFET]         InF                 (NULL      ).as(inFile              ) ] :Optional  :InputFETfileList\n");
    fprintf(stderr, "    [-i[nput]a[ngle]     InA                 (NULL      ).as(inFile              ) ] :Optional  :inputAngleList\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-o[ut]clog          OutLOG              (NULL      ).as(outFile             ) ] :Optional  :OutputCorValueLogFile\n");
    fprintf(stderr, "    [-o[ut]a[ngle]       OutA                (NULL      ).as(outFile             ) ] :Optional  :OutputAngleList\n");
    fprintf(stderr, "    [-o[ut]2d            Out2D               (NULL      ).as(outFile             ) ] :Optional  :OutputAngleListFormrc3Dto2D\n");
    fprintf(stderr, "    [-itm[ax]            ITMAX               (8         ).as(Integer             ) ] :Optional  :iterationMax\n");
    fprintf(stderr, "    [-dvm[ax]            DEVMAX              (3         ).as(Integer             ) ] :Optional  :sphereDevideMax\n");
    fprintf(stderr, "    [-mitm[ax]           MITMAX              (3         ).as(Integer             ) ] :Optional  :iterationMax Multiple\n");
    fprintf(stderr, "    [-mdvm[ax]           MDEVMAX             (3         ).as(Integer             ) ] :Optional  :sphereDevideMax Multiple\n");
    fprintf(stderr, "    [-ldn[um]            LDN                 (8         ).as(Integer             ) ] :Optional  :LongaxisDevideNum\n");
    fprintf(stderr, "    [-srl[imit]          SRL                 (0.0       ).as(Real                ) ] :Optional  :sphereReconstLimit\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (202       ).as(Integer             ) ] :Optional  :Mode\n");
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
