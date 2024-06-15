#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-I[nput array of file]In                  (NULL      ).as(inFileListNoOpen    ) ] :Essential :InputDataFiles\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-O[utput]                                                                     ] :Optional  :Output: averaged images: filename is xxxx.avg: xxxx is input filename.\n");
    fprintf(stderr, "    [-N[umberOfClusters] N                   (1         ).as(Integer             ) ] :Optional  :Number of clusters\n");
    fprintf(stderr, "    [-Min[imumCorrelation]Min                 (0.0       ).as(Real                ) ] :Optional  :Minimum: Correlation: Conditions for ending\n");
    fprintf(stderr, "    [-Iter[ation]                                                                  ] :Optional  :IterationFlag\n");
    fprintf(stderr, "    [-A[uto]R[otation]   AutoRotation        (72        ).as(Integer             ) ] :Optional  :AutoRotation: rotation divided by this value\n");
    fprintf(stderr, "    [-A[utoRot]Range     ARMin               (0         ).as(Real                ) \n                         ARMax               (360       ).as(Real                ) ] :Optional  :AutoRotationRange\n");
    fprintf(stderr, "    [-A[uto]R[otation]iter[ation]AutoRotationIteration(2         ).as(Integer             ) ] :Optional  :AutoRotationIteration\n");
    fprintf(stderr, "    [-A[uto]R[otation]MethodAutoRotationMethod  (0         ).as(Integer             ) ] :Optional  :Method for Correlation for Auto Rotation\n");
    fprintf(stderr, "    [-M[odeForCorrelation]correlationMode     (19        ).as(Integer             ) ] :Optional  :Correlation Mode for AutoRotation\n");
    fprintf(stderr, "    [-Log                Log                 (stdout    ).as(appendFile          ) ] :Optional  :Log: Output\n");
    fprintf(stderr, "    [-Log2               Log2                (NULL      ).as(appendFile          ) ] :Optional  :Log2: Output: ClusterNode Only\n");
    fprintf(stderr, "    [-LogIn              LogIn               (NULL      ).as(inFile              ) ] :Optional  :previousLog: Input\n");
    fprintf(stderr, "    [-prevF[ileNum]      prevFileNum         (0         ).as(Integer             ) ] :Optional  :previousLogFileNum: Input\n");
    fprintf(stderr, "    [-pthread            pthread             (0         ).as(Integer             ) ] :Optional  :pthread: Input\n");
    fprintf(stderr, "    [-NoRecalc                                                                     ] :Optional  :No recalculation of distances\n");
    fprintf(stderr, "    [-pvm                                                                          ] :Optional  :Parallel Analysis by PVM\n");
    fprintf(stderr, "    [-pvmList            pvmList             (NULL      ).as(inFile              ) ] :Optional  :pvmList: Input\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (2         ).as(Integer             ) ] :Optional  :Mode\n");
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
