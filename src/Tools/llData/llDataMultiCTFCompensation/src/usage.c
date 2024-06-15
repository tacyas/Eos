#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFileList          ) ] :Essential :Input: FileList\n");
    fprintf(stderr, "    [-M[odel]            Ref                 (NULL      ).as(inFile              ) ] :Essential :Input: Model Data\n");
    fprintf(stderr, "    [-l[ayerLine]        llInfo              (NULL      ).as(inFile              ) ] :Essential :Input: Layer Line Information\n");
    fprintf(stderr, "    [-A[verageFile]      Ave                 (NULL      ).as(outFile             ) ] :Essential :Output: AverageFile\n");
    fprintf(stderr, "    [-o[utput]           OutParam            (NULL      ).as(appendFile          ) ] :Optional  :Output: FittedParameter\n");
    fprintf(stderr, "    [-O[utput]           Out                 (NULL      ).as(outFileList         ) ] :Optional  :Output: FileList:  PhaseShift of Each Filament\n");
    fprintf(stderr, "    [-o2[utput]          OutParam2           (NULL      ).as(outFileList         ) ] :Optional  :Output: [phi, z] map\n");
    fprintf(stderr, "    [-P2[output]         OutParamP2          (NULL      ).as(outFile             ) ] :Optional  :Output: For P-P' \n");
    fprintf(stderr, "    [-N[oise]            Noise               (0.0       ).as(Real                ) ] :Optional  :Noise Ratio\n");
    fprintf(stderr, "    [-t[ruePitch]        truePitch           (761.4     ).as(Real                ) ] :Essential :truePitch[A]\n");
    fprintf(stderr, "    [-d[eltaR]           deltaR              (1.0       ).as(Real                ) ] :Optional  :deltaR[A]\n");
    fprintf(stderr, "    [-r[adial]           rmin                (1.0       ).as(Real                ) \n                         rmax                (1.0       ).as(Real                ) \n                         dr                  (1.0       ).as(Real                ) ] :Optional  :Radial[Ratio]\n");
    fprintf(stderr, "    [-p[hi]              phimin              (0.0       ).as(Real                ) \n                         phimax              (180.0     ).as(Real                ) \n                         dphi                (1.0       ).as(Real                ) ] :Optional  :Phi [degree]\n");
    fprintf(stderr, "    [-z[shift]           zmin                (0.0       ).as(Real                ) \n                         zmax                (180.0     ).as(Real                ) \n                         dz                  (1.0       ).as(Real                ) ] :Optional  :z [A]\n");
    fprintf(stderr, "    [-Rmax               Rmax                (0.1       ).as(Real                ) ] :Optional  :Rmax [/A]\n");
    fprintf(stderr, "    [-MaxIter[ation]     MaxIter             (1         ).as(Integer             ) ] :Optional  :MaxIteration\n");
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
