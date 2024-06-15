#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputDataFile\n");
    fprintf(stderr, "    [-i[nput]S[ource]fileInS                 (NULL      ).as(inFile              ) ] :Essential :InputSourceFile\n");
    fprintf(stderr, "    [-o[utput]E[xtract]  OutE                (NULL      ).as(inFile              ) ] :Essential :OutputFileForExtraction\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(appendFile          ) ] :Optional  :Output Log File\n");
    fprintf(stderr, "    [-o[utput]F[inal]    OutF                (stdout    ).as(outFile             ) ] :Optional  :OutputFinalFile\n");
    fprintf(stderr, "    [-r[oi]ROI           blx                 (0.0       ).as(Real                ) \n                         bly                 (0.0       ).as(Real                ) \n                         brx                 (0.0       ).as(Real                ) \n                         bry                 (0.0       ).as(Real                ) \n                         trx                 (0.0       ).as(Real                ) \n                         try                 (0.0       ).as(Real                ) \n                         tlx                 (0.0       ).as(Real                ) \n                         tly                 (0.0       ).as(Real                ) ] :Optional  :Rectangle ROI \n");
    fprintf(stderr, "    [-r[oi]Unbent        roiLine             (0.0       ).as(Real                ) ... ] :Variable  :\n");
    fprintf(stderr, "    [-x                  x                   (120       ).as(Real                ) ] :Optional  :x range for ROI or Unbent\n");
    fprintf(stderr, "    [-d[elta]dYmax       ddYmax              (0.9       ).as(Real                ) ] :Optional  :delta dY max\n");
    fprintf(stderr, "    [-d[elta]dYmin       ddYmin              (0.2       ).as(Real                ) ] :Optional  :delta dY mim\n");
    fprintf(stderr, "    [-T[ransepose]       T                   (0         ).as(Integer             ) ] :Optional  :corresponding to mrcImageTransepose mode\n");
    fprintf(stderr, "    [-maxd[elta]Y        maxdY               (12        ).as(Integer             ) ] :Optional  :Maximum number of layer line\n");
    fprintf(stderr, "    [-H[eight] R[ange]   HeightRange         (0         ).as(Integer             ) ] :Optional  :Height Range [Pixel]\n");
    fprintf(stderr, "    [-RMaxX              RMaxX               (0.05      ).as(Real                ) ] :Optional  :RMaxX [1/A] (supported mode 1)\n");
    fprintf(stderr, "    [-mag                mag                 (1.1       ).as(Real                ) ] :Optional  :magnification ratio\n");
    fprintf(stderr, "    [-truePitch          truePitch           (430       ).as(Real                ) ] :Optional  :True Pitch [A]\n");
    fprintf(stderr, "    [-PixelSize          PixelSize           (5         ).as(Real                ) ] :Optional  :Pixel Size [A]\n");
    fprintf(stderr, "    [-finaly             finaly              (0         ).as(Integer             ) ] :Optional  :final y [pixel] for extraction\n");
    fprintf(stderr, "    [-Ignore             Ignore              (0         ).as(Integer             ) ] :Optional  :Ignore the final y \n");
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
