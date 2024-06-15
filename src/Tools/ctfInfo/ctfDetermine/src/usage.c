#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile:  mrcImage\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(appendFile          ) ] :Essential :OutputDataFile: Parameters\n");
    fprintf(stderr, "    [-D[efocus]          Defocus             (0.0       ).as(Real                ) ] :Optional  :InitialDefocus[A]\n");
    fprintf(stderr, "    [-Cs                 Cs                  (1.7       ).as(Real                ) ] :Optional  :InitialCs[mm]\n");
    fprintf(stderr, "    [-Cc                 Cc                  (1.2       ).as(Real                ) ] :Optional  :InitialCs[mm]\n");
    fprintf(stderr, "    [-dE                 dE                  (0.2       ).as(Real                ) ] :Optional  :InitialCs[mm]\n");
    fprintf(stderr, "    [-Ac[cerratedVoltage]Ac                  (200       ).as(Real                ) ] :Optional  :Ac[kV]\n");
    fprintf(stderr, "    [-CutLow             CutLow              (0.05      ).as(Real                ) ] :Optional  :CutOffLowFrequncy[/A]\n");
    fprintf(stderr, "    [-CutHigh            CutHigh             (0.5       ).as(Real                ) ] :Optional  :CutOffHighFrequncy[/A]\n");
    fprintf(stderr, "    [-I0                 I0                  (1.0       ).as(Real                ) ] :Optional  :I0\n");
    fprintf(stderr, "    [-ratio              ratioOfAmpToPhase   (0.1       ).as(Real                ) ] :Optional  :ratioOfAmpToPhase\n");
    fprintf(stderr, "    [-Ai                 Ai                  (0.03      ).as(Real                ) ] :Optional  :IlluminationAngle[mrad]\n");
    fprintf(stderr, "    [-BofMTF             BofMTF              (15.0      ).as(Real                ) ] :Optional  :B of MTF [A]\n");
    fprintf(stderr, "    [-BofV[ibration]     BofVibration        (3.0       ).as(Real                ) ] :Optional  :B of Vibration [A]\n");
    fprintf(stderr, "    [-Mag[nification]    Magnification       (1.0       ).as(Real                ) ] :Optional  :Magnification\n");
    fprintf(stderr, "    [-[White]Noise       WhiteNoise          (0.0       ).as(Real                ) ] :Optional  :Signal/Noise Ratio\n");
    fprintf(stderr, "    [-[White]Noise2      WhiteNoise2         (0.0       ).as(Real                ) ] :Optional  :Signal/Noise Ratio\n");
    fprintf(stderr, "    [-MolcEnv            MolcEnv             (0.0       ).as(Real                ) ] :Optional  :Gaussian: Molcular Envelop [A]\n");
    fprintf(stderr, "    [-MolcEnv2           MolcEnvTable        (NULL      ).as(inFile              ) ] :Optional  :Table: Molcular Envelop\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-min                min                 (-10       ).as(Real                ) ] :Optional  :min of coefficient area\n");
    fprintf(stderr, "    [-max                max                 (10        ).as(Real                ) ] :Optional  :max of coefficient area\n");
    fprintf(stderr, "    [-s[tep]             step                (0.01      ).as(Real                ) ] :Optional  :step of coefficient\n");
    fprintf(stderr, "    [-d[egree]           degree              (6         ).as(Integer             ) ] :Optional  :agree of function\n");
    fprintf(stderr, "    [-S[ection]          section             (4         ).as(Integer             ) ] :Optional  :section number of fft\n");
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
