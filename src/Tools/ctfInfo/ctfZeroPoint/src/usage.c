#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputDataFile\n");
    fprintf(stderr, "    [-RMax               RMax                (0.1       ).as(Real                ) ] :Optional  :RMax[/A]\n");
    fprintf(stderr, "    [-dR                 dR                  (0.0001    ).as(Real                ) ] :Optional  :dR[/A]\n");
    fprintf(stderr, "    [-kV                 kV                  (200       ).as(Real                ) ] :Optional  :AccVol[kV]\n");
    fprintf(stderr, "    [-Cs                 Cs                  (2.1       ).as(Real                ) ] :Optional  :Cs[mm]\n");
    fprintf(stderr, "    [-df                 Defocus             (27000     ).as(Real                ) ] :Optional  :Defocus[A]:under(+)\n");
    fprintf(stderr, "    [-dfMin              MinDefocus          (0         ).as(Real                ) ] :Optional  :Min Defocus[A]\n");
    fprintf(stderr, "    [-dfMax              MaxDefocus          (200000    ).as(Real                ) ] :Optional  :Max Defocus[A]\n");
    fprintf(stderr, "    [-deltadf            DeltaDefocus        (2000      ).as(Real                ) ] :Optional  :Delta Defocus[A]\n");
    fprintf(stderr, "    [-A                  AoverP              (0.05      ).as(Real                ) ] :Optional  :AmplitudeContrast/PhaseContrast\n");
    fprintf(stderr, "    [-N                  N                   (1.0       ).as(Integer             ) ] :Optional  :Ordinal number of zero point\n");
    fprintf(stderr, "    [-Ain                Ain                 (0.02      ).as(Real                ) ] :Optional  :IlluminationAperture[mrad]\n");
    fprintf(stderr, "    [-ctfMode            ctfMode             (0         ).as(Integer             ) ] :Optional  :CTFMode\n");
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
