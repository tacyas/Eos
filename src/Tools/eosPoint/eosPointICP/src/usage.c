#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: eosPoint\n");
    fprintf(stderr, "    [-i[nput]t[ype]      InType              (2         ).as(Integer             ) ] :Optional  :eosPointType\n");
    fprintf(stderr, "    [-i[nput]Mat[rix]    InMat               (NULL      ).as(inFile              ) ] :Optional  :Input: Matrix3D for initial\n");
    fprintf(stderr, "    [-r[eference]        Ref                 (NULL      ).as(inFile              ) ] :Essential :Input: esoPoint\n");
    fprintf(stderr, "    [-r[eference]t[ype]  RefType             (2         ).as(Integer             ) ] :Optional  :Input: esoPoint\n");
    fprintf(stderr, "    [-r[eference]Mat[rix]RefMat              (NULL      ).as(inFile              ) ] :Optional  :Input: Matrix3D for initial\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-o[utput]t[ype]     OutType             (2         ).as(Integer             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-EAMode             EAMode              (ZEYS      ).as(String              ) ] :Optional  :Euler Angle\n");
    fprintf(stderr, "    [-R[atio]            Ratio               (1.0       ).as(Real                ) ] :Optional  :Mag\n");
    fprintf(stderr, "    [-Iter[ationLimit]   IterationLimit      (10000     ).as(Integer             ) ] :Optional  :IteretionLimit\n");
    fprintf(stderr, "    [-Pattern            Pattern             (10        ).as(Integer             ) ] :Optional  :Pickup Pattern\n");
    fprintf(stderr, "    [-Thres[hold]        ScoreThreshold      (0.0       ).as(Real                ) ] :Optional  :Threshold\n");
    fprintf(stderr, "    [-Omit               Omit                (100000.0  ).as(Real                ) ] :Optional  :OmitPointfrom Score\n");
    fprintf(stderr, "    [-Pick[upPercent]    Pickup              (0.8       ).as(Real                ) ] :Optional  :Pickup Percent\n");
    fprintf(stderr, "    [-flag2D             flag2D              (0         ).as(Integer             ) ] :Optional  :2D(1) or 3D(0)\n");
    fprintf(stderr, "    [-debug              Debug               (0         ).as(Integer             ) ] :Optional  :Debug Mode\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
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
