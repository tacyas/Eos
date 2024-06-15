#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input: Src\n");
    fprintf(stderr, "    [-k[ernel]           Kernel              (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input: Kernel\n");
    fprintf(stderr, "    [-k[ernel]centre     KernelCentre        (1         ).as(Integer             ) ] :Optional  :Input: Kernel Centre\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile::mrcImage   ) ] :Essential :Output: Dst\n");
    fprintf(stderr, "    [-o[utput]conv       OutConv             (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output: Conv*Dst to compare with in\n");
    fprintf(stderr, "    [-O[utput]           OutASCII            (stdout    ).as(outFile::ASCII      ) ] :Optional  :Output: Param\n");
    fprintf(stderr, "    [-O[utput]RMSD       OutRMSD             (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output: Param\n");
    fprintf(stderr, "    [-thresCTF           thresCTF            (1e-4      ).as(Real                ) ] :Optional  :threshold CTF for InverseFilter\n");
    fprintf(stderr, "    [-NSRatio            NSRatio             (0.0       ).as(Real                ) ] :Optional  :N/S Ratio for R-dependent Wiener Filter\n");
    fprintf(stderr, "    [-NSCoeff            NSCoeff             (0.0       ).as(Real                ) ] :Optional  :N/S Coeff for R-dependent Wiener Filter\n");
    fprintf(stderr, "    [-Pad3DMode          Pad3DMode           (1         ).as(Integer             ) ] :Optional  :lmrcImage3DPad Mode\n");
    fprintf(stderr, "    [-r[max]             r                   (0         ).as(Real                ) ] :Optional  :Pad3D: [pix] Threshold radius of signal.Default is min(Nx,Ny).\n");
    fprintf(stderr, "    [-w[idth]            w                   (1         ).as(Real                ) ] :Optional  :Pad3D: [pix] Width of slope. For mode 1.\n");
    fprintf(stderr, "    [-v[alue]            v                   (0         ).as(Real                ) ] :Optional  :Pad3D: Value of out of threshold.\n");
    fprintf(stderr, "    [-Floating                                                                     ] :Optional  :Pad3D: Floating\n");
    fprintf(stderr, "    [-maxIter            maxIter             (0         ).as(Integer             ) ] :Optional  :maxIteration for Iterative\n");
    fprintf(stderr, "    [-minRMSD            minRMSD             (0.0       ).as(Real                ) ] :Optional  :min of MRSD for Iterative\n");
    fprintf(stderr, "    [-lambda             lambda              (0.5       ).as(Real                ) ] :Optional  :lambda for Iterative\n");
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
