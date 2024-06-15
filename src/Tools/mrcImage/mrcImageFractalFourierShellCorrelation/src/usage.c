#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :Input: mrcImage Input\n");
    fprintf(stderr, "    [-r[eference]        Ref                 (NULL      ).as(inFile              ) ] :Essential :Input: mrcImage Reference\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output: ResolutionMap\n");
    fprintf(stderr, "    [-t[hreshold]        Threshold           (0.5       ).as(Real                ) ] :Optional  :Input: Threshold\n");
    fprintf(stderr, "    [-s[tep]x            stepx               (1         ).as(Real                ) ] :Optional  :Input: step x\n");
    fprintf(stderr, "    [-s[tep]y            stepy               (1         ).as(Real                ) ] :Optional  :Input: step y\n");
    fprintf(stderr, "    [-s[tep]z            stepz               (1         ).as(Real                ) ] :Optional  :Input: step z\n");
    fprintf(stderr, "    [-maxN               maxN                (32        ).as(Real                ) ] :Optional  :Input: max partIn.HeaderN\n");
    fprintf(stderr, "    [-scaling[ up]       scaling             (1.25      ).as(Real                ) ] :Optional  :Input: scaling up\n");
    fprintf(stderr, "    [-get[ mode]         getMode             (0         ).as(Integer             ) ] :Optional  :Input:mrcPixelDataGetMode\n");
    fprintf(stderr, "    [-Log                Log                 (NULL      ).as(outFile             ) ] :Optional  :Output: Log File\n");
    fprintf(stderr, "    [-xmin               xmin                (0         ).as(Real                ) ] :Optional  :Input: xmin\n");
    fprintf(stderr, "    [-ymin               ymin                (0         ).as(Real                ) ] :Optional  :Input: ymin\n");
    fprintf(stderr, "    [-zmin               zmin                (0         ).as(Real                ) ] :Optional  :Input: zmin\n");
    fprintf(stderr, "    [-xmax               xmax                (0         ).as(Real                ) ] :Optional  :Input: xmax\n");
    fprintf(stderr, "    [-ymax               ymax                (0         ).as(Real                ) ] :Optional  :Input: ymax\n");
    fprintf(stderr, "    [-zmax               zmax                (0         ).as(Real                ) ] :Optional  :Input: zmax\n");
    fprintf(stderr, "    [-d[ensity]          densityThreshold    (0         ).as(Real                ) ] :Optional  :Input: density threshold\n");
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
