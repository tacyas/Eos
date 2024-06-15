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
    fprintf(stderr, "    [-Shape              Shape               (NULL      ).as(outFile::mrcImage   ) ] :Optional  :Output\n");
    fprintf(stderr, "    [-n[Cube]            nCube               (0         ).as(Integer             ) ] :Optional  :Mode\n");
    fprintf(stderr, "    [-Refine                                                                       ] :Optional  :Refine\n");
    fprintf(stderr, "    [-r[adius]           minR                (3         ).as(Integer             ) \n                         maxR                (5         ).as(Integer             ) \n                         delR                (1         ).as(Integer             ) ] :Optional  :Radius[pixel]\n");
    fprintf(stderr, "    [-l[ength]           minL                (3         ).as(Integer             ) \n                         maxL                (5         ).as(Integer             ) \n                         delL                (1         ).as(Integer             ) ] :Optional  :Length[pixel]\n");
    fprintf(stderr, "    [-Phi                minPhi              (0.0       ).as(Real                ) \n                         maxPhi              (359.0     ).as(Real                ) \n                         delPhi              (45.0      ).as(Real                ) ] :Optional  :around z-axis[degree]\n");
    fprintf(stderr, "    [-Theta              minTheta            (0.0       ).as(Real                ) \n                         maxTheta            (359.0     ).as(Real                ) \n                         delTheta            (45.0      ).as(Real                ) ] :Optional  :around x-axis[degree]\n");
    fprintf(stderr, "    [-Psi                minPsi              (0.0       ).as(Real                ) \n                         maxPsi              (350.0     ).as(Real                ) \n                         delPsi              (45.0      ).as(Real                ) ] :Optional  :around x-axis[degree]\n");
    fprintf(stderr, "    [-thres[Zscore]      thresZscore         (1.0       ).as(Real                ) ] :Optional  :Zscore\n");
    fprintf(stderr, "    [-interp[olationMode]interpMode          (0         ).as(Integer             ) ] :Optional  :interpMode\n");
    fprintf(stderr, "    [-O[utput]V[ector]ModeOVMode              (0         ).as(Integer             ) ] :Optional  :Output-Mode\n");
    fprintf(stderr, "    [-O[utput]V[ector]BILDOutVectorBILD       (NULL      ).as(outFile::BILD       ) ] :Optional  :Output:BILD-vector\n");
    fprintf(stderr, "    [-O[utput]V[ector]   OutVector           (NULL      ).as(String              ) ] :Optional  :Output:vector basename\n");
    fprintf(stderr, "    [-arrow[Shape]       ArrowR1             (0.1       ).as(Real                ) \n                         ArrowR2             (0.4       ).as(Real                ) \n                         ArrowRho            (0.75      ).as(Real                ) ] :Optional  :ArrowShape\n");
    fprintf(stderr, "    [-zoom[Vector]       ZoomVector          (1.0       ).as(Real                ) ] :Optional  :Zoom\n");
    fprintf(stderr, "    [-arrowColorDisk     ArrowColorDisk0     (0.0       ).as(Real                ) \n                         ArrowColorDisk1     (1.0       ).as(Real                ) \n                         ArrowColorDisk2     (0.0       ).as(Real                ) ] :Optional  :ArrowColorDisk\n");
    fprintf(stderr, "    [-arrowColorSylinder ArrowColorSylinder0 (1.0       ).as(Real                ) \n                         ArrowColorSylinder1 (0.0       ).as(Real                ) \n                         ArrowColorSylinder2 (0.0       ).as(Real                ) ] :Optional  :ArrowColorSylinder\n");
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
