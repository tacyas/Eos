#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input:binary(BandW)\n");
    fprintf(stderr, "    [-r[erencence]       Ref                 (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input:reference(density)\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile::ASCII      ) ] :Optional  :Output:\n");
    fprintf(stderr, "    [-o[utput]GC         OutGC               (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output:gc\n");
    fprintf(stderr, "    [-o[utput]L[abel]    OutLabel            (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output:Label\n");
    fprintf(stderr, "    [-o[utput]P[eprimeter]OutPerimeter        (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output:Perimeter\n");
    fprintf(stderr, "    [-o[utput]C[hainID]  OutChain            (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output:ChainID\n");
    fprintf(stderr, "    [-o[utput]S[urfaceArea]OutSurfaceArea      (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output:SurfaceArea\n");
    fprintf(stderr, "    [-o[utput]D[ensityWeightedArea]OutDensityWeightedArea(NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output:DensityWeightedArea\n");
    fprintf(stderr, "    [-n[eighbor]         neighbor            (0         ).as(Integer             ) ] :Optional  :Neighbor: [4(0)|8 or 6(0)|18|26]\n");
    fprintf(stderr, "    [-d[ensity]          InDensity           (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input:density\n");
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
