#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Optional  :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-t                  turn                (-6        ).as(Integer             ) ] :Optional  :Turn\n");
    fprintf(stderr, "    [-u                  unit                (13        ).as(Integer             ) ] :Optional  :Unit\n");
    fprintf(stderr, "    [-N                  nstrand             (1         ).as(Integer             ) ] :Optional  :N-strand\n");
    fprintf(stderr, "    [-Y1                 Y1                  (36        ).as(Integer             ) ] :Optional  :Y1 [pixel]: The Position of LayerLine which l = |t| i.e., |n|=1&&m=0 for the first time\n");
    fprintf(stderr, "    [-Y0                 Y0                  (78        ).as(Integer             ) ] :Optional  :Y0 [pixel]: The Position of LayerLine which n = 0 , l != 0 for the first time\n");
    fprintf(stderr, "    [-rmax               rmax                (250       ).as(Real                ) ] :Optional  :rmax[A]\n");
    fprintf(stderr, "    [-Rmax               Rmax                (0.1       ).as(Real                ) ] :Optional  :Rmax[/A]\n");
    fprintf(stderr, "    [-lx                 lx                  (5.0       ).as(Real                ) ] :Optional  :Pixel Size\n");
    fprintf(stderr, "    [-ly                 ly                  (5.0       ).as(Real                ) ] :Optional  :Pixel Size\n");
    fprintf(stderr, "    [-nx                 nx                  (1000.0    ).as(Real                ) ] :Optional  :Image Size[Pixel]\n");
    fprintf(stderr, "    [-ny                 ny                  (1000.0    ).as(Real                ) ] :Optional  :Image Size[Pixel]\n");
    fprintf(stderr, "    [-center             center              (500.0     ).as(Real                ) ] :Optional  :Center of nx (center of filament)[Pixel]\n");
    fprintf(stderr, "    [-layerline          layerline           (21.0      ).as(Real                ) ] :Optional  :Number of Layer Line\n");
    fprintf(stderr, "    [-Ax                 Ax                  (5000.0    ).as(Real                ) ] :Optional  :Length of nx (lx * nx)[A]\n");
    fprintf(stderr, "    [-dY                 dY                  (12.0      ).as(Real                ) ] :Optional  :Range of Layer Line[pixel]\n");
    fprintf(stderr, "    [-truePitch          truePitch           (430       ).as(Real                ) ] :Optional  :True Pitch\n");
    fprintf(stderr, "    [-PixelSize          PixelSize           (5         ).as(Real                ) ] :Optional  :Pixel Size [A]\n");
    fprintf(stderr, "    [-deltadY            deltadY             (0.5       ).as(Real                ) ] :Optional  :A range of deltadY to determine dY.[pixel]\n");
    fprintf(stderr, "    [-m[ode]             mode                (1         ).as(Integer             ) ] :Optional  :Mode\n");
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
