#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile::mrcImage    ) ] :Essential :Input\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile::mrcImage   ) ] :Essential :Output\n");
    fprintf(stderr, "    [-r[oi]              blx                 (0.0       ).as(Real                ) \n                         bly                 (0.0       ).as(Real                ) \n                         brx                 (0.0       ).as(Real                ) \n                         bry                 (0.0       ).as(Real                ) \n                         trx                 (0.0       ).as(Real                ) \n                         try                 (0.0       ).as(Real                ) \n                         tlx                 (0.0       ).as(Real                ) \n                         tly                 (0.0       ).as(Real                ) ] :Optional  :Rectangle ROI \n");
    fprintf(stderr, "    [-x                  WidthBeforeExpansion(1.0       ).as(Real                ) ] :Optional  :Width  before expansion: /* Default is set by -r */\n");
    fprintf(stderr, "    [-y                  HeightBeforeExpansion(1.0       ).as(Real                ) ] :Optional  :Height before expansion: /* Default is set by -r */\n");
    fprintf(stderr, "    [-a[ngle]            Angle               (0.0       ).as(Real                ) ] :Optional  :This value [degree] is added to angle of current source image.\n");
    fprintf(stderr, "    [-W                  WidthAfterExpansion (1.0       ).as(Real                ) ] :Optional  :Width  after expansion[Pixel]\n");
    fprintf(stderr, "    [-H                  HeightAfterExpansion(1.0       ).as(Real                ) ] :Optional  :Height after expansion[Pixel]: \n\t\tROI Size is (10,20):\n\t\t\tIf -W 30 -H 40, out (30,40)\n\t\t\tIf -W 30, out (30, 20*30/10)\n\t\t\tIf -H 40, out (10*40/20,40)\n\t\t\t\tIf omitted, out (10,20)\n");
    fprintf(stderr, "    [-Shift              ShiftX              (0.0       ).as(Real                ) \n                         ShiftY              (0.0       ).as(Real                ) ] :Optional  :ROI ARea Shift [Pixel]\n");
    fprintf(stderr, "    [-turePitch          truePitch           (430.0     ).as(Real                ) ] :Optional  :truePitch [A]\n");
    fprintf(stderr, "    [-dY                 dY                  (0.0       ).as(Real                ) ] :Optional  :Number of turePitch\n");
    fprintf(stderr, "    [-Ly                 Ly                  (5.0       ).as(Real                ) ] :Optional  :Header Length y [A/Pixel]\n");
    fprintf(stderr, "    [-S[hrink]           Shrink              (1         ).as(Integer             ) ] :Optional  :When inputfile is shrinked\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-M[ode]             ROIShapeMode        (0         ).as(Integer             ) ] :Optional  :RoiShapeMode\n");
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
