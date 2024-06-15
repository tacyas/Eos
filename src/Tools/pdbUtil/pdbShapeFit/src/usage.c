#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]pdb[File]   InPDB               (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-i[nput]mrc[File]   InMRC               (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-C[ontour]          Contour             (0.0       ).as(Real                ) ] :Essential :Contour\n");
    fprintf(stderr, "    [-C[ontour]M[ode]    ContourMode         (0         ).as(Integer             ) ] :Optional  :ContourMode: refer to mrcImageContourSurfaceCreate\n");
    fprintf(stderr, "    [-o[utput of ]mrc    OutMRC              (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-o[utput of ]txt    OutTxt              (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
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
    fprintf(stderr, "    [-P[DB]C[ontour]M[ode]surfaceMode         (0         ).as(Integer             ) ] :Optional  :PDB SurfaceMode: refer to pdbSurface\n");
    fprintf(stderr, "    [-order              order               (1.7       ).as(Real                ) ] :Optional  :order: refer to pdbSurface\n");
    fprintf(stderr, "    [-refine             refine              (2         ).as(Integer             ) ] :Optional  :refine: refer to pdbSurface\n");
    fprintf(stderr, "    [-size               size                (3         ).as(Integer             ) ] :Optional  :size: refer to pdbSurface\n");
    fprintf(stderr, "    [-weight             weight              (100       ).as(Real                ) ] :Optional  :weight: refer to pdbSurface\n");
    fprintf(stderr, "    [-mergin             mergin              (3.0       ).as(Real                ) ] :Optional  :mergin: refer to pdbSurface\n");
    fprintf(stderr, "    [-thres              thresHold           (0.0       ).as(Real                ) ] :Optional  :threshold: refer to pdbSurface\n");
    fprintf(stderr, "    [-I[nverse]                                                                    ] :Optional  :Black is High Density.\n");
    fprintf(stderr, "    [-Centre                                                                       ] :Optional  :Filament-axis is x=0, y=0\n");
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
