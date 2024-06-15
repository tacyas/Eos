#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            InList              (NULL      ).as(inFileListNoOpen    ) ] :Essential :Input: filelist\n");
    fprintf(stderr, "    [-O[utput]           Outclassification   (NULL      ).as(outFile             ) ] :Essential :Output: ClassificationDataFile\n");
    fprintf(stderr, "    [-o[utput]c[lassification]i[ntegration]r[ate]OutClassificationIntegrationRate(NULL      ).as(outFile             ) ] :Optional  :OutputClassificationIntegrationRate: classificationIntegrationRatefile\n");
    fprintf(stderr, "    [-o[utput]d[istance] OutDistance         (NULL      ).as(outFile             ) ] :Optional  :OutputDistance: distancefile\n");
    fprintf(stderr, "    [-o[utput]d[istance]r[ate]OutDistanceRate     (NULL      ).as(outFile             ) ] :Optional  :OutputDistanceRate: distanceRatefile\n");
    fprintf(stderr, "    [-o[utput]u[pper]d[istance]n[umberOfClasses]OutUpperDistanceRate(NULL      ).as(outFile             ) ] :Optional  :OutputUpperDistanceNumberOfClasses: upperDistanceRatefile\n");
    fprintf(stderr, "    [-o[utput]u[pper]d[istance]c[lassificationDatafile]OutClassName        (NULL      ).as(outFile             ) ] :Optional  :OutputUpperDistanceClassificationDatafile: ClassificationDatafile\n");
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
