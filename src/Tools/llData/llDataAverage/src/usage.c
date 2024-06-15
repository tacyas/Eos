#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-M[odel]            Model               (NULL      ).as(inFile              ) ] :Essential :Input: ModelFileName(llData)\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFileList          ) ] :Essential :Input: InputDataFile\n");
    fprintf(stderr, "    [-l[ayer]            llInfo              (NULL      ).as(inFile              ) ] :Essential :Input: Layer Line Information\n");
    fprintf(stderr, "    [-A[verage]          Ave                 (NULL      ).as(outFile             ) ] :Essential :Output: Averaged File Name\n");
    fprintf(stderr, "    [-o[utput]           OutParam            (stdout    ).as(appendFile          ) ] :Optional  :Output: FittedParameter\n");
    fprintf(stderr, "    [-o2[utput]          OutParam2           (NULL      ).as(outFileList         ) ] :Optional  :Output: FittedParameter(phi, z)\n");
    fprintf(stderr, "    [-O[utput]           Out                 (NULL      ).as(outFileList         ) ] :Optional  :Output: FittedData\n");
    fprintf(stderr, "    [-P2[plot]           P2                  (NULL      ).as(outFile             ) ] :Optional  :Output: P2PlotData\n");
    fprintf(stderr, "    [-t[ruePitch]        truePitch           (1.0       ).as(Real                ) ] :Optional  :True Pitch\n");
    fprintf(stderr, "    [-d[eltaR]           dR                  (1.0       ).as(Real                ) ] :Optional  :deltaR\n");
    fprintf(stderr, "    [-r[adial]           rmin                (1.0       ).as(Real                ) \n                         rmax                (1.0       ).as(Real                ) \n                         dr                  (1.0       ).as(Real                ) ] :Optional  :Radial[Ratio]\n");
    fprintf(stderr, "    [-p[hi]              phimin              (0.0       ).as(Real                ) \n                         phimax              (180.0     ).as(Real                ) \n                         dphi                (5.0       ).as(Real                ) ] :Optional  :Phi [degree]\n");
    fprintf(stderr, "    [-z[shift]           zmin                (0.0       ).as(Real                ) \n                         zmax                (60.0      ).as(Real                ) \n                         dz                  (5.0       ).as(Real                ) ] :Optional  :z [A]\n");
    fprintf(stderr, "    [-withoutAntiPole                                                              ] :Optional  :Not Allow Antipole\n");
    fprintf(stderr, "    [-C[utValue]         CutValue            (1.0       ).as(Real                ) ] :Optional  :CutValue\n");
    fprintf(stderr, "    [-pvm                pvm                 (0         ).as(Integer             ) ] :Optional  :PVM: \n");
    fprintf(stderr, "    [-pvmList            pvmList             (stdin     ).as(inFile              ) ] :Optional  :PVM: HostList\n");
    fprintf(stderr, "    [-pvmList            Log                 (stdout    ).as(appendFile          ) ] :Optional  :PVM: HostList\n");
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
