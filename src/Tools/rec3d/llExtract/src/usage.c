#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-t[itle]            Title               (NULL      ).as(String              ) ] :Optional  :Title[80]\n");
    fprintf(stderr, "    [-s[tep]             xStep               (1.0       ).as(Real                ) \n                         yStep               (1.0       ).as(Real                ) ] :Optional  :Step[A]\n");
    fprintf(stderr, "    [-M[ax]              MaxX                (1.0       ).as(Real                ) \n                         MaxY                (1.0       ).as(Real                ) ] :Optional  :Max[GridUnit]\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Optional  :InputDataFile[mrcImage]\n");
    fprintf(stderr, "    [-1[output]          Nea                 (NULL      ).as(outFile             ) ] :Optional  :NearSide[llData]\n");
    fprintf(stderr, "    [-2[output]          Far                 (NULL      ).as(outFile             ) ] :Optional  :FarSide [llData]\n");
    fprintf(stderr, "    [-R[otationAngle]    RotationAngle       (0.0       ).as(Real                ) ] :Optional  :Ratation Angle [Degree]\n");
    fprintf(stderr, "    [-O[mega]            Omega               (0.0       ).as(Real                ) ] :Optional  :Omega[Degree]\n");
    fprintf(stderr, "    [-S[hear]            Shear               (0.0       ).as(Real                ) ] :Optional  :Shear[Degree]\n");
    fprintf(stderr, "    [-I[every]           ievery              (0         ).as(Integer             ) ] :Optional  :ievery\n");
    fprintf(stderr, "    [-axl                axl                 (0.0       ).as(Real                ) ] :Optional  :axl\n");
    fprintf(stderr, "    [-ayl                ayl                 (0.0       ).as(Real                ) ] :Optional  :ayl\n");
    fprintf(stderr, "    [-x[Shift]           xShift              (0.0       ).as(Real                ) ] :Optional  :[GridUnit]\n");
    fprintf(stderr, "    [-l[lMax]            llMax               (0         ).as(Integer             ) ] :Optional  :\n");
    fprintf(stderr, "    [-d[elRInv]          delRInv             (0.0       ).as(Real                ) ] :Optional  :[A]\n");
    fprintf(stderr, "    [-f[lagOutputInfo]                                                             ] :Optional  :\n");
    fprintf(stderr, "    [-L[ayerLineInfo]    n                   (0         ).as(Integer             ) \n                         l                   (0         ).as(Integer             ) \n                         Y                   (0.0       ).as(Real                ) \n                         leftMin             (0.0       ).as(Real                ) \n                         leftMax             (0.0       ).as(Real                ) \n                         rightMin            (0.0       ).as(Real                ) \n                         rightMax            (0.0       ).as(Real                ) \n                         weight              (1.0       ).as(Real                ) ... ] :Variable  :\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
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
