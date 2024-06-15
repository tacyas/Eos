#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :mrcImage(FT):InputDataFile\n");
    fprintf(stderr, "    [-o1[utput]          SepNea              (NULL      ).as(outFile             ) ] :Essential :llData(Near):OutputDataFile\n");
    fprintf(stderr, "    [-o2[utput]          SepFar              (NULL      ).as(outFile             ) ] :Essential :llData(Far ):OutputDataFile\n");
    fprintf(stderr, "    [-O1[utput]          MixNea              (NULL      ).as(outFile             ) ] :Optional  :llData(Mix Near):OutputDataFile\n");
    fprintf(stderr, "    [-O2[utput]          MixFar              (NULL      ).as(outFile             ) ] :Optional  :llData(Mix Far ):OutputDataFile\n");
    fprintf(stderr, "    [-delRInv            delRInv             (0.0       ).as(Real                ) ] :Optional  :delRInv: [A]: Get default value from mrcImage\n");
    fprintf(stderr, "    [-truePitch          truePitch           (0.0       ).as(Real                ) ] :Optional  :truePitch: [A]: Get default value from mrcImage\n");
    fprintf(stderr, "    [-rMax               rMax                (50.0      ).as(Real                ) ] :Essential :rMax: [ A]\n");
    fprintf(stderr, "    [-RMax               RMax                (0.2       ).as(Real                ) ] :Optional  :RMax: [/A]\n");
    fprintf(stderr, "    [-xShift             xShift              (0.0       ).as(Real                ) ] :Optional  :xShift: [pixel]: Get default value(Centre) from mrcImage\n");
    fprintf(stderr, "    [-L[og]              Log                 (stdout    ).as(outFile             ) ] :Optional  :LogFile\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Essential :ConfigurationFile\n");
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
