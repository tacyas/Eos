#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In2D                (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input: 2D(FFT)\n");
    fprintf(stderr, "    [-i[nput]3d          In3D                (NULL      ).as(inFile::            ) \n                         volPath             (NULL      ).as(String              ) ] :Essential :Input: 3D(FFT)\n");
    fprintf(stderr, "    [-Prior              Prior               (NULL      ).as(inFile::            ) \n                         PriPath             (./        ).as(String              ) ] :Optional  :Input: Prior\n");
    fprintf(stderr, "    [-EulerMode          EulerMode           (YOYS      ).as(String              ) ] :Optional  :Input: EulerMode\n");
    fprintf(stderr, "    [-Rot1               Rot1Start           (0.0       ).as(Real                ) \n                         Rot1End             (360.0     ).as(Real                ) \n                         Rot1Delta           (10        ).as(Real                ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-Rot2               Rot2Start           (0.0       ).as(Real                ) \n                         Rot2End             (360.0     ).as(Real                ) \n                         Rot2Delta           (10        ).as(Real                ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-Rot3               Rot3Start           (0.0       ).as(Real                ) \n                         Rot3End             (360.0     ).as(Real                ) \n                         Rot3Delta           (10        ).as(Real                ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-trans[late]        TransX              (0.0       ).as(Real                ) \n                         TransY              (0.0       ).as(Real                ) ] :Optional  :Input: Translation\n");
    fprintf(stderr, "    [-InterpMode         InterpMode          (0         ).as(Integer             ) ] :Optional  :Interpolation Mode\n");
    fprintf(stderr, "    [-o[utput]           Out1                (stdout    ).as(outFile             ) ] :Optional  :Output: PosteriorProb\n");
    fprintf(stderr, "    [-o[utput]L[ikelihood]OutLikelihood       (stdout    ).as(outFile             ) ] :Optional  :Output: Likelihood\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-L[ikelihood]mode   Lcalcmode           (0         ).as(Integer             ) \n                         Lmode1              (0.0       ).as(Real                ) \n                         Lmode2              (0.0       ).as(Real                ) ] :Optional  :Input: Likelihoodmode\n");
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
