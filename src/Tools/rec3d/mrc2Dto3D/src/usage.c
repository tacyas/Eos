#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-I[nput]            In2                 (NULL      ).as(inFileListNoOpen    ) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-each                                                                         ] :Optional  :Read each projection file if necessary, not at once.\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-O[utput]           Out2                (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile[2DMulti]\n");
    fprintf(stderr, "    [-Rmax               Rmax                (1.0       ).as(Real                ) ] :Optional  :Rmax: High Cut [/A]\n");
    fprintf(stderr, "    [-single             single              (1         ).as(Integer             ) ] :Optional  :SingleTiltMode\n");
    fprintf(stderr, "    [-singleFilter       singleFilter        (0         ).as(Integer             ) ] :Optional  :SingleFilterMode\n");
    fprintf(stderr, "    [-InterpolationMode  InterpolationMode   (1         ).as(Integer             ) ] :Optional  :InterpolationMode\n");
    fprintf(stderr, "    [-Double                                                                       ] :Optional  :DoubleTiltMode\n");
    fprintf(stderr, "    [-DoubleCounter      DoubleCounter       (NULL      ).as(outFile             ) ] :Optional  :DoubleCounter\n");
    fprintf(stderr, "    [-CounterThreshold   CounterThreshold    (1e-6      ).as(Real                ) ] :Optional  :CounterThreshold\n");
    fprintf(stderr, "    [-CounterThresholdModeCounterThresholdMode(0         ).as(Integer             ) ] :Optional  :CounterThresholdMode\n");
    fprintf(stderr, "    [-WeightMode         WeightMode          (0         ).as(Integer             ) ] :Optional  :WeightMode\n");
    fprintf(stderr, "    [-thicknessWeight                                                              ] :Optional  :ThicknessWeight\n");
    fprintf(stderr, "    [-Sub[Sampling]      SubSampling         (1         ).as(Integer             ) ] :Optional  :SubSampling: [pixel]\n");
    fprintf(stderr, "    [-PlusXrot                                                                     ] :Optional  :plus x-rotation by 180 for rasmol.\n");
    fprintf(stderr, "    [-N                  Nx                  (0         ).as(Integer             ) \n                         Ny                  (0         ).as(Integer             ) \n                         Nz                  (0         ).as(Integer             ) ] :Optional  :OutputSize\n");
    fprintf(stderr, "    [-SIRT                                                                         ] :Optional  :by SIRT\n");
    fprintf(stderr, "    [-max[Iter]          maxIter             (30        ).as(Integer             ) ] :Optional  :MaxIteration for SIRT\n");
    fprintf(stderr, "    [-rms                rms                 (1.0       ).as(Real                ) ] :Optional  :Ending Conditions: rms for SIRT\n");
    fprintf(stderr, "    [-CTF[Info]          CTFInfo             (NULL      ).as(inFileList          ) ] :Optional  :CTFInfo: for SIRT\n");
    fprintf(stderr, "    [-pthread            pthreadMax          (1         ).as(Integer             ) ] :Optional  :pthread: max\n");
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
