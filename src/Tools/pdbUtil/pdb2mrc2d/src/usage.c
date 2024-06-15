#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile(2D)\n");
    fprintf(stderr, "    [-O[utput]           Out3D               (NULL      ).as(outFile             ) ] :Optional  :OutputDataFile(3D)\n");
    fprintf(stderr, "    [-d[elta]            dx                  (5.0       ).as(Real                ) \n                         dy                  (5.0       ).as(Real                ) ] :Essential :delta: dx[A] dy[A]\n");
    fprintf(stderr, "    [-s[tart]            sx                  (0.0       ).as(Real                ) \n                         sy                  (0.0       ).as(Real                ) ] :Optional  :start: startx[A] starty[A]: When -s was not set, image centre is the origin(0,0,0)\n");
    fprintf(stderr, "    [-n[umber]           nx                  (0         ).as(Integer             ) \n                         ny                  (0         ).as(Integer             ) ] :Essential :N:     nx ny (image size)\n");
    fprintf(stderr, "    [-Rot[ation]         rotnx               (1         ).as(Integer             ) \n                         rotny               (1         ).as(Integer             ) ] :Optional  :rotnx rotny\n");
    fprintf(stderr, "    [-S[tart]            srotx               (0.0       ).as(Real                ) \n                         sroty               (0.0       ).as(Real                ) \n                         srotz               (0.0       ).as(Real                ) ] :Optional  :start(rotx roty rotz):ZXY\n");
    fprintf(stderr, "    [-startE[uler]A[ngle]sRotMode            (YOYS      ).as(String              ) \n                         sRot1               (0.0       ).as(Real                ) \n                         sRot2               (0.0       ).as(Real                ) \n                         sRot3               (0.0       ).as(Real                ) ] :Optional  :EulerAngle: Start Angle\n");
    fprintf(stderr, "    [-E[uler]A[ngle]Mode RotMode             (YOYS      ).as(String              ) ] :Optional  :RotationMode\n");
    fprintf(stderr, "    [-E[uler]A[ngle]Rot1 dRot1               (5.0       ).as(Real                ) \n                         minRot1             (0.0       ).as(Real                ) \n                         maxRot1             (180.0     ).as(Real                ) ] :Optional  :FirstRotation\n");
    fprintf(stderr, "    [-E[uler]A[ngle]Rot2 dRot2               (5.0       ).as(Real                ) \n                         minRot2             (0.0       ).as(Real                ) \n                         maxRot2             (180.0     ).as(Real                ) ] :Optional  :SecondRotation\n");
    fprintf(stderr, "    [-w[eight]           Weight              (1.0       ).as(Real                ) ] :Optional  :weight\n");
    fprintf(stderr, "    [-sig[ma]            Sigma               (0.0       ).as(Real                ) ] :Optional  :Sigma[A]:Atom radius\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-cuda               cudaDeviceID        (0         ).as(Integer             ) ] :Optional  :UseCuda\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode: 0 Merc; 1: Earth\n");
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
