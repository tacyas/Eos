#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-r[eference]        Ref                 (NULL      ).as(inFile              ) ] :Essential :ReferenceDataFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :Output Optimum [text]\n");
    fprintf(stderr, "    [-oP[utput]          Out2                (NULL      ).as(outFile             ) ] :Optional  :Output Distribution [mrc image]\n");
    fprintf(stderr, "    [-oC[utput]          OutC                (NULL      ).as(outFile             ) ] :Optional  :Output CTF Information file\n");
    fprintf(stderr, "    [-oF[utput]          OutF                (NULL      ).as(outFile             ) ] :Optional  :Output Result FFT[mrc image]\n");
    fprintf(stderr, "    [-kV                 kV                  (200       ).as(Real                ) ] :Optional  :AccVol[kV]\n");
    fprintf(stderr, "    [-Cs                 Cs                  (2.1       ).as(Real                ) ] :Optional  :Cs[mm]\n");
    fprintf(stderr, "    [-Ain                Ain                 (0.02      ).as(Real                ) ] :Optional  :IlluminationAperture[mrad]\n");
    fprintf(stderr, "    [-W[hiteNoise]       WhiteNoise          (1.0       ).as(Real                ) ] :Optional  :\n");
    fprintf(stderr, "    [-df                 mindf               (0.0       ).as(Real                ) \n                         maxdf               (200000    ).as(Real                ) \n                         deldf               (1000      ).as(Real                ) ] :Optional  :df[A] for in\n");
    fprintf(stderr, "    [-AoverP             minAoverP           (0.0       ).as(Real                ) \n                         maxAoverP           (1.0       ).as(Real                ) \n                         delAoverP           (0.01      ).as(Real                ) ] :Optional  :AoverP[A] for in\n");
    fprintf(stderr, "    [-Rmin               Rmin                (0.0       ).as(Real                ) ] :Optional  :Rmin[/A]\n");
    fprintf(stderr, "    [-Rmax               Rmax                (0.1       ).as(Real                ) ] :Optional  :Rmax[/A]\n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]F[ilter type]mF                  (1         ).as(Integer             ) ] :Optional  :Filter Type\n");
    fprintf(stderr, "    [-m[ode]W[ight type] mW                  (0         ).as(Integer             ) ] :Optional  :Wight Type\n");
    fprintf(stderr, "    [-m[ode]S[um type]   mS                  (0         ).as(Integer             ) ] :Optional  :Sum Type\n");
    fprintf(stderr, "    [-m[ode]C[TF Info type]mC                  (0         ).as(Integer             ) ] :Optional  :CTF Information Type\n");
    fprintf(stderr, "    [-M[ode]             M                   (0         ).as(Integer             ) ] :Optional  :ref Type\n");
    fprintf(stderr, "    [-PixelSize          PixelSize           (5         ).as(Integer             ) ] :Optional  :Pixel Size [A]\n");
    fprintf(stderr, "    [-Width              Width               (120       ).as(Integer             ) ] :Optional  :Pad Width [pixel]\n");
    fprintf(stderr, "    [-truePitch          truePitch           (430       ).as(Real                ) ] :Optional  :True Pitch [A]\n");
    fprintf(stderr, "    [-dfRef              firstDf             (70000     ).as(Real                ) \n                         withinDf            (1000      ).as(Real                ) ] :Optional  :dfRef for ref\n");
    fprintf(stderr, "    [-AoverPRef          firstAoverP         (0.05      ).as(Real                ) \n                         withinAoverP        (0.01      ).as(Real                ) ] :Optional  :A over P Ref for ref\n");
    fprintf(stderr, "    [-MaxIter            maxiter             (10        ).as(Integer             ) ] :Optional  :MaxIteration for ref\n");
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
