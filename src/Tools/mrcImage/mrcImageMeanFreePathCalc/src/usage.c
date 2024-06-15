#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input:mrcImage\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile::ASCII      ) ] :Optional  :Output:distribution\n");
    fprintf(stderr, "    [-O[utput]w[hite]all OutWhiteAll         (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output: white+whiteEdge\n");
    fprintf(stderr, "    [-O[utput]w[hite]    OutWhite            (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output: white\n");
    fprintf(stderr, "    [-O[utput]b[lack]all OutBlackAll         (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output: black+blackEdge\n");
    fprintf(stderr, "    [-O[utput]b[lack]    OutBlack            (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output: black\n");
    fprintf(stderr, "    [-O[utput]w[hite]e[dge]OutWhiteEdge        (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output: whiteEdge\n");
    fprintf(stderr, "    [-O[utput]b[lack]e[dge]OutBlackEdge        (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output: blackEdge\n");
    fprintf(stderr, "    [-O[utput]dir[ection]Direction           (direction ).as(String              ) ] :Optional  :Output: basename.[0|1|2] vector for any\n");
    fprintf(stderr, "    [-l[ine]t[hickness]  LineThicknessX      (1         ).as(Real                ) \n                         LineThicknessY      (1         ).as(Real                ) ] :Optional  :[pixel]\n");
    fprintf(stderr, "    [-l[ine]m[ode]       LineMode            (0         ).as(Integer             ) ] :Optional  :LineMode\n");
    fprintf(stderr, "    [-l[ine]s[hape]      LineShape           (0         ).as(Integer             ) ] :Optional  :LineShape\n");
    fprintf(stderr, "    [-deltaPhi           deltaPhi            (30        ).as(Real                ) ] :Optional  :deltaPhi\n");
    fprintf(stderr, "    [-deltaTheta         deltaTheta          (30        ).as(Real                ) ] :Optional  :deltaTheta\n");
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
