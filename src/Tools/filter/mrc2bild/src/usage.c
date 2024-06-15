#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input:mrcImage\n");
    fprintf(stderr, "    [-i[nput]3           In0                 (NULL      ).as(inFile::mrcImage    ) \n                         In1                 (NULL      ).as(inFile::mrcImage    ) \n                         In2                 (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input:mrcImagex3\n");
    fprintf(stderr, "    [-i[nput]4           InX                 (NULL      ).as(inFile::mrcImage    ) \n                         InY                 (NULL      ).as(inFile::mrcImage    ) \n                         InZ                 (NULL      ).as(inFile::mrcImage    ) \n                         InWeight            (NULL      ).as(inFile::mrcImage    ) ] :Optional  :Input:mrcImagex4\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile::BILD       ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-color              Red                 (1.0       ).as(Real                ) \n                         Green               (1.0       ).as(Real                ) \n                         Blue                (1.0       ).as(Real                ) ] :Optional  :Color\n");
    fprintf(stderr, "    [-zoom               Zoom                (1.0       ).as(Real                ) ] :Optional  :Zoom\n");
    fprintf(stderr, "    [-arrow[Shape]       R1                  (0.1       ).as(Real                ) \n                         R2                  (0.4       ).as(Real                ) \n                         Rho                 (0.75      ).as(Real                ) ] :Optional  :Arrow\n");
    fprintf(stderr, "    [-skip               skipX               (1         ).as(Integer             ) \n                         skipY               (1         ).as(Integer             ) \n                         skipZ               (1         ).as(Integer             ) ] :Optional  :SkipVoxel\n");
    fprintf(stderr, "    [-rainbow            RainbowMode         (0         ).as(Integer             ) ] :Optional  :Raibow\n");
    fprintf(stderr, "    [-rainbowThresLow    RainbowThresLow     (0         ).as(Real                ) ] :Optional  :RainbowTresLow(color)\n");
    fprintf(stderr, "    [-rainbowThresHigh   RainbowThresHigh    (0         ).as(Real                ) ] :Optional  :RainbowTresLow(color)\n");
    fprintf(stderr, "    [-rainbowRangeLow    RainbowRangeLow     (0         ).as(Real                ) ] :Optional  :RainbowRange(visible)\n");
    fprintf(stderr, "    [-rainbowRangeHigh   RainbowRangeHigh    (0         ).as(Real                ) ] :Optional  :RainbowRange(visible)\n");
    fprintf(stderr, "    [-rangeX             RangeXMin           (0         ).as(Real                ) \n                         RangeXMax           (-1        ).as(Real                ) ] :Optional  :RangeX\n");
    fprintf(stderr, "    [-rangeY             RangeYMin           (0         ).as(Real                ) \n                         RangeYMax           (-1        ).as(Real                ) ] :Optional  :RangeY\n");
    fprintf(stderr, "    [-rangeZ             RangeZMin           (0         ).as(Real                ) \n                         RangeZMax           (-1        ).as(Real                ) ] :Optional  :RangeZ\n");
    fprintf(stderr, "    [-rangeR             RangeRCX            (0         ).as(Real                ) \n                         RangeRCY            (0         ).as(Real                ) \n                         RangeRCZ            (0         ).as(Real                ) \n                         RangeRR             (0         ).as(Real                ) ] :Optional  :RangeR\n");
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
