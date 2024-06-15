#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-I[nput]            InOriginal          (NULL      ).as(inFile              ) ] :Essential :Input: Original \n");
    fprintf(stderr, "    [-i[nput]            InPrevious          (NULL      ).as(inFile              ) ] :Essential :Input: Previous \n");
    fprintf(stderr, "    [-i[nput]c[ounter]   FFTInCount          (NULL      ).as(inFile              ) ] :Optional  :Input: CounterforWeight FourierSpace \n");
    fprintf(stderr, "    [-o[utput]           Out                 (NULL      ).as(outFile             ) ] :Essential :Output: Next    \n");
    fprintf(stderr, "    [-t[ime]             t                   (1         ).as(Integer             ) ] :Optional  :Number of time: Iteration(Real Space)\n");
    fprintf(stderr, "    [-fromp[oint]1       x00                 (0         ).as(Integer             ) \n                         y00                 (0         ).as(Integer             ) \n                         z00                 (0         ).as(Integer             ) ] :Optional  :First value near origin of coordinates: x00[pixel] y00[pixel] z00[pixel] \n");
    fprintf(stderr, "    [-top[oint]1         x01                 (2         ).as(Integer             ) \n                         y01                 (2         ).as(Integer             ) \n                         z01                 (2         ).as(Integer             ) ] :Optional  :target value: x01[pixel] y01[pixel] z01[pixel] \n");
    fprintf(stderr, "    [-fromp[oint]2       x10                 (0         ).as(Integer             ) \n                         y10                 (0         ).as(Integer             ) \n                         z10                 (0         ).as(Integer             ) ] :Optional  :First value far from origin of coordinates: x10[pixel] y10[pixel] z10[pixel] \n");
    fprintf(stderr, "    [-top[oint]2         x11                 (0         ).as(Integer             ) \n                         y11                 (0         ).as(Integer             ) \n                         z11                 (0         ).as(Integer             ) ] :Optional  :target value: x11[pixel] y11[pixel] z11[pixel] \n");
    fprintf(stderr, "    [-c[onfig]           configFile          (NULL      ).as(inFile              ) ] :Optional  :ConfigurationFile\n");
    fprintf(stderr, "    [-m[ode]             mode                (0         ).as(Integer             ) ] :Essential :RealSpaceCalculating\n");
    fprintf(stderr, "    [-LabelingMode       labelingmode        (0         ).as(Integer             ) ] :Optional  :LabelingMode\n");
    fprintf(stderr, "    [-max[value]         max                 (800       ).as(Integer             ) ] :Optional  :Density Max value:Support Constraint(%) \n");
    fprintf(stderr, "    [-min[value]         min                 (200       ).as(Integer             ) ] :Optional  :Density Min value:Support Constraint(%) \n");
    fprintf(stderr, "    [-sh[ape]            shape               (0         ).as(Integer             ) ] :Optional  :Shape:0(Rectangule),1(Globe)\n");
    fprintf(stderr, "    [-h[alf]v[alue]p[oint]hvp                 (0.0       ).as(Real                ) ] :Optional  :Half value point(/[A])\n");
    fprintf(stderr, "    [-Inverse                                                                      ] :Optional  :Inverse\n");
    fprintf(stderr, "    [-nM[olecule]        nMolecule           (1         ).as(Integer             ) ] :Optional  :Number of Molecule\n");
    fprintf(stderr, "    [-M[olecularWeight]  MolecularWeight     (80000     ).as(Integer             ) ] :Optional  :MolecularWeight\n");
    fprintf(stderr, "    [-D[ensity]          Density             (1.35      ).as(Real                ) ] :Optional  :Density(g/cm3)\n");
    fprintf(stderr, "    [-counter            incounter           (3.0       ).as(Real                ) ] :Optional  :Counter(Fourier Space)\n");
    fprintf(stderr, "    [-d[elta]Density     deltaDens           (100.0     ).as(Real                ) ] :Optional  :Delta (Convergence)\n");
    fprintf(stderr, "    [-d[elta]Area        deltaArea           (100.0     ).as(Real                ) ] :Optional  :Area (Convergence)\n");
    fprintf(stderr, "    [-sub[traction]      sub                 (0.2       ).as(Real                ) ] :Optional  :Subtraction(Convergence)\n");
    fprintf(stderr, "    [-ratio              ratio               (0.3       ).as(Real                ) ] :Optional  :Ratio(Convergence)\n");
    fprintf(stderr, "    [-t[ime]max          tmax                (1000      ).as(Integer             ) ] :Optional  :Time Max(Convergence)\n");
    fprintf(stderr, "    [-w[eight]d[elta]    WeightDelta         (0.1       ).as(Real                ) ] :Optional  :WeightDelta(Fourier Space)\n");
    fprintf(stderr, "    [-w[eight]m[ax]      WeightMax           (2         ).as(Integer             ) ] :Optional  :WeightMax(Fourier Space)\n");
    fprintf(stderr, "    [-Subtraction                                                                  ] :Optional  :Subtraction(Real Space)\n");
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
