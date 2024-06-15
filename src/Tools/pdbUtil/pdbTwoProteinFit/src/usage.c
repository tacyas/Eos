#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-i[nput]res[idue]   InResidue           (NULL      ).as(inFile              ) ] :Optional  :ResidueInformationOfInputData\n");
    fprintf(stderr, "    [-i[nput]sel[ectResidue]SelectIn            (NULL      ).as(outFile             ) ] :Optional  :Output: Selected residue of in after fitting\n");
    fprintf(stderr, "    [-r[ef]              Ref                 (NULL      ).as(inFile              ) ] :Essential :ReferenceDataFile\n");
    fprintf(stderr, "    [-r[ef]res[idue]     RefResidue          (NULL      ).as(inFile              ) ] :Optional  :ResidueInfomationOfReferenceData\n");
    fprintf(stderr, "    [-r[ef]sel[ectResidue]SelectRef           (NULL      ).as(outFile             ) ] :Optional  :Output: Selected residue of after fitting\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-o[utput]Matrix     Matrix              (stdout    ).as(outFile             ) ] :Optional  :OutputMatrix\n");
    fprintf(stderr, "    [-o[utput]Param      Param               (stdout    ).as(outFile             ) ] :Optional  :OutputParam\n");
    fprintf(stderr, "    [-o[utput]Dis[tance] outDis              (stdout    ).as(outFile             ) ] :Optional  :Output: PDB Distance as Temp\n");
    fprintf(stderr, "    [-o[utput]Dis[tance]2outDis2             (stdout    ).as(outFile             ) ] :Optional  :Output: Distance List for Ca\n");
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
