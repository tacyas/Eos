#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile(AutoRotationCorrelationResult)\n");
    fprintf(stderr, "    [-I[nput]            InData              (NULL      ).as(inFile              ) ] :Optional  :InputDataFile(test Data)\n");
    fprintf(stderr, "    [-r[ef]              Ref                 (NULL      ).as(inFile              ) ] :Essential :ReferenceFile\n");
    fprintf(stderr, "    [-pdb                PDB                 (NULL      ).as(inFile              ) ] :Optional  :ReferenceFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-max                Max                 (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile[MaxImage]\n");
    fprintf(stderr, "    [-maxRot             MaxRot              (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile[MaxImageWithRotationAnShift]\n");
    fprintf(stderr, "    [-maxpdb             MaxPDB              (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile[MaxImage]\n");
    fprintf(stderr, "    [-maxpdbForRasmol    MaxPDBForRasmol     (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile[MaxImage]\n");
    fprintf(stderr, "    [-S[tartRot]         Sx                  (0.0       ).as(Real                ) \n                         Sy                  (0.0       ).as(Real                ) \n                         Sz                  (0.0       ).as(Real                ) ] :Optional  :StartRot[DEGREE]\n");
    fprintf(stderr, "    [-top                Top                 (1         ).as(Integer             ) ] :Optional  :TopEntry\n");
    fprintf(stderr, "    [-wish                                                                         ] :Optional  :Display3D\n");
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
