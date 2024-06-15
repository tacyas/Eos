#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]pdb[File]   InPdb               (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-i[nput]mrc[File]   InMrc               (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput of ]mrc    OutMrc              (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-o[utput of ]txt    OutTxt              (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-o[utput of ]par    OutPar              (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-o[utput of ]pdb    OutPDB              (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-xmin               xmin                (0         ).as(Real                ) ] :Optional  :xmin for fitting\n");
    fprintf(stderr, "    [-xmax               xmax                (0         ).as(Real                ) ] :Optional  :xmax for fitting\n");
    fprintf(stderr, "    [-xd[elta]           xDelta              (1         ).as(Real                ) ] :Optional  :delta x for fitting\n");
    fprintf(stderr, "    [-ymin               ymin                (0         ).as(Real                ) ] :Optional  :ymin for fitting\n");
    fprintf(stderr, "    [-ymax               ymax                (0         ).as(Real                ) ] :Optional  :ymax for fitting\n");
    fprintf(stderr, "    [-yd[elta]           yDelta              (1         ).as(Real                ) ] :Optional  :delta y for fitting\n");
    fprintf(stderr, "    [-zmin               zmin                (0         ).as(Real                ) ] :Optional  :zmin for fitting\n");
    fprintf(stderr, "    [-zmax               zmax                (82        ).as(Real                ) ] :Optional  :zmax for fitting\n");
    fprintf(stderr, "    [-zd[elta]           zDelta              (1         ).as(Real                ) ] :Optional  :delta z for fitting\n");
    fprintf(stderr, "    [-E[uler]A[ngle]     EulerAngle          (ZOYS      ).as(String              ) ] :Optional  :Euler Angle for three-angle\n");
    fprintf(stderr, "    [-phimin             phimin              (0         ).as(Real                ) ] :Optional  :phimin for fitting(degree)\n");
    fprintf(stderr, "    [-phimax             phimax              (194       ).as(Real                ) ] :Optional  :phimax for fitting(degree)\n");
    fprintf(stderr, "    [-phid[elta]         phiDelta            (2         ).as(Real                ) ] :Optional  :delta phi for fitting(degree)\n");
    fprintf(stderr, "    [-psimin             psimin              (0         ).as(Real                ) ] :Optional  :psimin for fitting(degree)\n");
    fprintf(stderr, "    [-psimax             psimax              (0         ).as(Real                ) ] :Optional  :psimax for fitting(degree)\n");
    fprintf(stderr, "    [-psid[elta]         psiDelta            (2         ).as(Real                ) ] :Optional  :delta psi for fitting(degree)\n");
    fprintf(stderr, "    [-thetamin           thetamin            (0         ).as(Real                ) ] :Optional  :thetamin for fitting(degree)\n");
    fprintf(stderr, "    [-thetamax           thetamax            (0         ).as(Real                ) ] :Optional  :thetamax for fitting(degree)\n");
    fprintf(stderr, "    [-thetad[elta]       thetaDelta          (2         ).as(Real                ) ] :Optional  :delta theta for fitting(degree)\n");
    fprintf(stderr, "    [-n[ormalize]w[eight]normalizeWeight     (100000000.0).as(Real                ) ] :Optional  :weight for normalize\n");
    fprintf(stderr, "    [-n[ormalize]C[ontour]normalizeContour    (0.0       ).as(Real                ) ] :Optional  :Contour Level for Normalize\n");
    fprintf(stderr, "    [-I[nverse]                                                                    ] :Optional  :Black is High Density.\n");
    fprintf(stderr, "    [-Zminus                                                                       ] :Optional  :Shift to -z\n");
    fprintf(stderr, "    [-Tfactor                                                                      ] :Optional  :Consider T factor\n");
    fprintf(stderr, "    [-T[ factor ]lim[it] Tlim                (60        ).as(Real                ) ] :Optional  :The atom will be neglected\n");
    fprintf(stderr, "    [-Centre                                                                       ] :Optional  :Filament-axis is x=0, y=0\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-C[ontour]          contourLevel        (0.0       ).as(Real                ) ... ] :Variable  :ContourLevel\n");
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
