#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-Nx[Number of x]    Nx                  (0         ).as(Integer             ) ] :Optional  :Nx:Default Nx of inputfile\n");
    fprintf(stderr, "    [-Ny[Number of y]    Ny                  (0         ).as(Integer             ) ] :Optional  :Ny:Default Ny of inputfile\n");
    fprintf(stderr, "    [-Nz[Number of z]    Nz                  (0         ).as(Integer             ) ] :Optional  :Nz:Default Nz of inputfile\n");
    fprintf(stderr, "    [-Cx[Center x]       Cx                  (0         ).as(Real                ) ] :Optional  :Cetnter x position of extracted image.Default is center of iuput image.\n");
    fprintf(stderr, "    [-Cy[Center y]       Cy                  (0         ).as(Real                ) ] :Optional  :Cetnter y position of extracted image.Default is center of iuput image.\n");
    fprintf(stderr, "    [-Cz[Center z]       Cz                  (0         ).as(Real                ) ] :Optional  :Cetnter z position of extracted image.Default is center of iuput image.\n");
    fprintf(stderr, "    [-even                                                                         ] :Optional  :all dimensions of N are even. \n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-M[ode2]            mode2               (0         ).as(Integer             ) ] :Optional  :Mode2\n");
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
