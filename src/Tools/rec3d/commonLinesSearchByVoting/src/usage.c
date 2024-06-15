#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Optional  :InputCorrelationMapList\n");
    fprintf(stderr, "    [-i[nput]c[ommonLines]InC                 (NULL      ).as(inFile              ) ] :Optional  :InputCommonLinesList\n");
    fprintf(stderr, "    [-i[nput]c[orrect]c[ommonLines]InCC                (NULL      ).as(inFile              ) ] :Optional  :InputCorrectCommonLinesList\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputFilteredCommonLinesList\n");
    fprintf(stderr, "    [-o[utput]a[ll]      OutA                (NULL      ).as(outFile             ) ] :Optional  :OutputAllCommonLinesList\n");
    fprintf(stderr, "    [-o[utput]d[etecting]r[ate]OutDR               (NULL      ).as(outFile             ) ] :Optional  :OutputDetectingRate\n");
    fprintf(stderr, "    [-o[utput]d[etecting]r[ate]a[ll]OutDRA              (NULL      ).as(outFile             ) ] :Optional  :OutputDetectingRateALL\n");
    fprintf(stderr, "    [-o[utput]p[eaks]h[istgram]OutPH               (NULL      ).as(outFile             ) ] :Optional  :OutputPeaksHistgram\n");
    fprintf(stderr, "    [-e[stimation]n[umber]en                  (1         ).as(Integer             ) ] :Optional  :EstimationNumber\n");
    fprintf(stderr, "    [-th[resholdLevel]   th                  (1         ).as(Integer             ) ] :Optional  :ThresholdLevel\n");
    fprintf(stderr, "    [-histgramCreate[Flag]                                                          ] :Optional  :HistgramCreateFlag\n");
    fprintf(stderr, "    [-extend[VotingFlag]                                                           ] :Optional  :ExtendVotingFlag\n");
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
