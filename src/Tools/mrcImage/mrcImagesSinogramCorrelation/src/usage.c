#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-I[nputList]        In                  (NULL      ).as(inFileList          ) ] :Essential :InputDataFileList\n");
    fprintf(stderr, "    [-o[utput]H[eader]   OutHeader           (test      ).as(String              ) ] :Optional  :OutputDataFileHeader\n");
    fprintf(stderr, "    [-R[sults]d[irectoryname]Rd                  (Result    ).as(String              ) ] :Optional  :output results directory name\n");
    fprintf(stderr, "    [-N[ormalCorrelation]d[irectoryname]Nd                  (Normal    ).as(String              ) ] :Optional  :directory name of output normalcorrelation in results directory\n");
    fprintf(stderr, "    [-D[erivation]1[DCorrelation]d[irectoryname]D1d                 (Derivation1D).as(String              ) ] :Optional  :directory name of output derivation1Dcorrelation in results directory\n");
    fprintf(stderr, "    [-D[erivation]2[DCorrelation]d[irectoryname]D2d                 (Derivation2D).as(String              ) ] :Optional  :directory name of output derivation2Dcorrelation in results directory\n");
    fprintf(stderr, "    [-L[engthCorrelation]d[irectoryname]Ld                  (Length    ).as(String              ) ] :Optional  :directory name of output lengthcorrelation in results directory\n");
    fprintf(stderr, "    [-C[orrelation]E[xtension]CorrelationExtension(cor       ).as(String              ) ] :Optional  :output correlation file extension\n");
    fprintf(stderr, "    [-L[ist]E[xtension]  ListExtension       (list      ).as(String              ) ] :Optional  :output file list extension\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-N[ormalCorrelation]m[ode]Nmode               (0         ).as(Integer             ) ] :Optional  :\n");
    fprintf(stderr, "    [-D[erivation]1[DCorrelation]m[ode]D1mode              (0         ).as(Integer             ) ] :Optional  :\n");
    fprintf(stderr, "    [-D[erivation]2[DCorrelation]m[ode]D2mode              (0         ).as(Integer             ) ] :Optional  :\n");
    fprintf(stderr, "    [-L[engthCorrelation]m[ode]Lmode               (0         ).as(Integer             ) ] :Optional  :\n");
    fprintf(stderr, "    [-L[ength]T[hreshold]M[ode]LengthThresholdMode (0         ).as(Integer             ) ] :Optional  :LengthThresholdMode\n");
    fprintf(stderr, "    [-L[ength]T[hreshold]M[ode]LengthThresholdRatio(0.25      ).as(Real                ) ] :Optional  :LengthThresholdRatio\n");
    fprintf(stderr, "    [-C[reate]M[ode]     CM                  (0         ).as(Integer             ) ] :Optional  :CreateMode\n");
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
