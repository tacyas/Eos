#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input:mrcImage\n");
    fprintf(stderr, "    [-t[epmlate]         Template            (%%d.roi   ).as(String              ) ] :Optional  :Template for InputFile \n");
    fprintf(stderr, "    [-H[ighForThres]     ThresHigh           (0.0       ).as(Real                ) ] :Optional  :HighThres\n");
    fprintf(stderr, "    [-L[owForThres]      ThresLow            (0.0       ).as(Real                ) ] :Optional  :LowThres\n");
    fprintf(stderr, "    [-Zoom               Zoom                (1.0       ).as(Real                ) ] :Optional  :Zoom for InputFile \n");
    fprintf(stderr, "    [-Inverse                                                                      ] :Optional  :Inverse (HighValue(dark)<->LowValue(bright)) for InputFile \n");
    fprintf(stderr, "    [-o[utput]           Out                 (.EosLog   ).as(String              ) ] :Optional  :OutputLogFile\n");
    fprintf(stderr, "    [-def[ault]          Default             (~/.Eos/Display2).as(String              ) ] :Optional  :OutputLogFile\n");
    fprintf(stderr, "    [-display            geometry            (:0.0      ).as(String              ) ] :Optional  :OutputLogFile\n");
    fprintf(stderr, "    [-geometry           display             (1024x1024+0+0).as(String              ) ] :Optional  :OutputLogFile\n");
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
