#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-i[nput of ]f[lags] InFlags             (NULL      ).as(inFile              ) ] :Optional  :InputFlagsFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :OutputDataFile\n");
    fprintf(stderr, "    [-dist[ance]         distance            (2.5       ).as(Real                ) ] :Optional  :DistanceOfSections\n");
    fprintf(stderr, "    [-zmin[imum]         zmin                (0.0       ).as(Real                ) ] :Optional  :Minimum of Z\n");
    fprintf(stderr, "    [-zmax[imum]         zmax                (90.0      ).as(Real                ) ] :Optional  :Maximum of Z\n");
    fprintf(stderr, "    [-f[lag]m[ode]       flagMode            (13        ).as(Integer             ) ] :Optional  :flag mode\n");
    fprintf(stderr, "    [-r[adius]           radius              (1.0       ).as(Real                ) ] :Optional  :radius of the circle\n");
    fprintf(stderr, "    [-c[ircle]l[ine]w[idth]clinewidth          (0.1       ).as(Real                ) ] :Optional  :circle line width\n");
    fprintf(stderr, "    [-p[eptide bond]l[ine]w[idth]plinewidth          (0.1       ).as(Real                ) ] :Optional  :peptide bond line width\n");
    fprintf(stderr, "    [-fontsize           fontsize            (2.0       ).as(Real                ) ] :Optional  :font size\n");
    fprintf(stderr, "    [-A[bsolute]S[caleofPSFile]scale               (1.0       ).as(Real                ) ] :Optional  :absolute scale of PS file (-AS 1 := 1 mm/A)\n");
    fprintf(stderr, "    [-shiftx             shiftx              (0.0       ).as(Real                ) ] :Optional  :pdb Shift x [A]\n");
    fprintf(stderr, "    [-shifty             shifty              (0.0       ).as(Real                ) ] :Optional  :pdb Shift y [A]\n");
    fprintf(stderr, "    [-shiftz             shiftz              (0.0       ).as(Real                ) ] :Optional  :pdb Shift z [A]\n");
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
