#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Optional  :Output: correlation\n");
    fprintf(stderr, "    [-O[utput]           Out2                (stdout    ).as(outFile             ) ] :Optional  :Output: SymmetryInformation \n");
    fprintf(stderr, "    [-A[verage]          Avg                 (NULL      ).as(outFile             ) ] :Optional  :Output: Average\n");
    fprintf(stderr, "    [-centreMode         centreMode          (1         ).as(Integer             ) ] :Optional  :Input: 0 : Gravity of Centre; 1 : Search n-fold\n");
    fprintf(stderr, "    [-t1[threshold1]     threshold1          (1.8       ).as(Real                ) ] :Optional  :Threshold of CheckByAdd\n");
    fprintf(stderr, "    [-t2[threshold2]     threshold2          (0.9       ).as(Real                ) ] :Optional  :Threshold in deciding the symmetry number\n");
    fprintf(stderr, "    [-m1[mode1]          mode1               (3         ).as(Integer             ) ] :Optional  :Mode of Check\n");
    fprintf(stderr, "    [-m2[mode2]          mode2               (2         ).as(Integer             ) ] :Optional  :Mode of Substruction\n");
    fprintf(stderr, "    [-dr[delta r]        dr                  (1         ).as(Real                ) ] :Optional  :Delta r of outputfile.\n");
    fprintf(stderr, "    [-dtheta[delta theta]dtheta              (1         ).as(Real                ) ] :Optional  :Delta theta of outputfile.[DEGREE]\n");
    fprintf(stderr, "    [-n[umber]           n                   (10        ).as(Integer             ) ] :Optional  :Check to the number.\n");
    fprintf(stderr, "    [-n[umber]Range      nmin                (2         ).as(Integer             ) \n                         nmax                (10        ).as(Integer             ) ] :Optional  :Check to the number.\n");
    fprintf(stderr, "    [-In                 Image               (NULL      ).as(inFileList          ) \n                         Back                (NULL      ).as(inFileList          ) ] :Optional  :InputDataFile: Image and Back\n");
    fprintf(stderr, "    [-rangex             minx                (-3        ).as(Real                ) \n                         maxx                (3         ).as(Real                ) \n                         delx                (1         ).as(Real                ) ] :Optional  :Input: \n");
    fprintf(stderr, "    [-rangey             miny                (-3        ).as(Real                ) \n                         maxy                (3         ).as(Real                ) \n                         dely                (1         ).as(Real                ) ] :Optional  :Input: \n");
    fprintf(stderr, "    [-rangez             minz                (0         ).as(Real                ) \n                         maxz                (0         ).as(Real                ) \n                         delz                (1         ).as(Real                ) ] :Optional  :Input: \n");
    fprintf(stderr, "    [-rrange             rmin                (0         ).as(Real                ) \n                         rmax                (-1        ).as(Real                ) ] :Optional  :Input: Rrange[A]\n");
    fprintf(stderr, "    [-Algorythm                                                                    ] :Optional  :Algorythm\n");
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
