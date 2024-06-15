#include <stdio.h>
#include <stdlib.h>
#include "../inc/config.h"

void
usage(char* thisProgram)
{
    fprintf(stderr, "Usage: %s\n", thisProgram);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    [-i[nput]            In                  (NULL      ).as(inFile              ) ] :Essential :InputImageFile\n");
    fprintf(stderr, "    [-o[utput]           Out                 (stdout    ).as(outFile             ) ] :Optional  :OutputImageFile\n");
    fprintf(stderr, "    [-H[ighThreshold]    thresHigh           (0.0       ).as(Real                ) ] :Optional  :High Threshold\n");
    fprintf(stderr, "    [-L[owThreshold]     thresLow            (1.0       ).as(Real                ) ] :Optional  :Low Threshold\n");
    fprintf(stderr, "    [-Section            section             (z         ).as(Character           ) ] :Optional  :[z|x|y]Section: Def: z-section\n");
    fprintf(stderr, "    [-x[Section]         xMin                (0         ).as(Integer             ) \n                         xMax                (0         ).as(Integer             ) ] :Optional  :x section\n");
    fprintf(stderr, "    [-y[Section]         yMin                (0         ).as(Integer             ) \n                         yMax                (0         ).as(Integer             ) ] :Optional  :y section\n");
    fprintf(stderr, "    [-z[Section]         zMin                (0         ).as(Integer             ) \n                         zMax                (0         ).as(Integer             ) ] :Optional  :z section\n");
    fprintf(stderr, "    [-S[cale]            Scale               (1.0       ).as(Real                ) ] :Optional  :Scale(Centre is Bottom Left): -S 1 := 1 mm/pixel\n");
    fprintf(stderr, "    [-A[bsolute]S[cale]  AbScale             (1.0       ).as(Real                ) ] :Optional  :Scale(Centre is Bottom Left): -AS 1 := 1 mm/A (Real) or 1 mm/A-1 (Fourier Space)\n");
    fprintf(stderr, "    [-E[nlarge]          Enlarge             (1.0       ).as(Real                ) ] :Optional  :Enlargement(image center is center)\n");
    fprintf(stderr, "    [-center             cx                  (0.0/* in case of FT or N.x/2.0 in case of Image*/).as(Real                ) \n                         cy                  (0.0/* in case of FT or N.y/2.0 in case of Image */).as(Real                ) ] :Optional  :Center of a printed image\n");
    fprintf(stderr, "    [-C[ontour]          contourLevel        (1.0       ).as(Real                ) ... ] :Variable  :ContourLevel\n");
    fprintf(stderr, "    [-I[nverse]                                                                    ] :Optional  :Black is High Density.\n");
    fprintf(stderr, "    [-A[uto]                                                                       ] :Optional  :HighThres=Mean-SD, LowThres=Mean+SD\n");
    fprintf(stderr, "    [-AC[ontour]         AutoContour         (10        ).as(Integer             ) ] :Optional  :Auto Contour(thresHigh <-> mean)\n");
    fprintf(stderr, "    [-PC[ontour]         PeakContour         (10        ).as(Integer             ) ] :Optional  :Peak Contour(thresHigh <-> (mean+thresHigh)/2\n");
    fprintf(stderr, "    [-AC[ontour]2        AutoContour2        (10        ).as(Integer             ) ] :Optional  :Auto Contour2(thresHigh <-> thresLow)\n");
    fprintf(stderr, "    [-Y[expand]          Yexpand             (1         ).as(Real                ) ] :Optional  :Y-axis expanding\n");
    fprintf(stderr, "    [-RGB                Red                 (0         ).as(Real                ) \n                         Green               (0         ).as(Real                ) \n                         Blue                (0         ).as(Real                ) ] :Optional  :Contour Color Mode: RGB\n");
    fprintf(stderr, "    [-RGBGradient        RedFirst            (0         ).as(Real                ) \n                         GreenFirst          (0         ).as(Real                ) \n                         BlueFirst           (0         ).as(Real                ) \n                         RedLast             (0         ).as(Real                ) \n                         GreenLast           (0         ).as(Real                ) \n                         BlueLast            (0         ).as(Real                ) ] :Optional  :Contour Color GradientMode: RGB\n");
    fprintf(stderr, "    [-HSB                Hue                 (0         ).as(Real                ) \n                         Saturation          (0         ).as(Real                ) \n                         Brightness          (0         ).as(Real                ) ] :Optional  :Contour Color Mode: HSB\n");
    fprintf(stderr, "    [-HSBGradient        HueFirst            (0         ).as(Real                ) \n                         SaturationFirst     (0         ).as(Real                ) \n                         BrightnessFirst     (0         ).as(Real                ) \n                         HueLast             (0         ).as(Real                ) \n                         SaturationLast      (0         ).as(Real                ) \n                         BrightnessLast      (0         ).as(Real                ) ] :Optional  :Contour Color GradientMode: HSB\n");
    fprintf(stderr, "    [-LineColourRGB      LineRed             (0         ).as(Real                ) \n                         LineGreen           (0         ).as(Real                ) \n                         LineBlue            (0         ).as(Real                ) ] :Optional  :Contour Color Mode: RGB\n");
    fprintf(stderr, "    [-LineColourRGBGradientLineRedFirst        (0         ).as(Real                ) \n                         LineGreenFirst      (0         ).as(Real                ) \n                         LineBlueFirst       (0         ).as(Real                ) \n                         LineRedLast         (0         ).as(Real                ) \n                         LineGreenLast       (0         ).as(Real                ) \n                         LineBlueLast        (0         ).as(Real                ) ] :Optional  :Contour Color GradientMode: RGB\n");
    fprintf(stderr, "    [-LineColourHSB      LineHue             (0         ).as(Real                ) \n                         LineSaturation      (0         ).as(Real                ) \n                         LineBrightness      (0         ).as(Real                ) ] :Optional  :Contour Color Mode: HSB\n");
    fprintf(stderr, "    [-LineColourHSBGradientLineHueFirst        (0         ).as(Real                ) \n                         LineSaturationFirst (0         ).as(Real                ) \n                         LineBrightnessFirst (0         ).as(Real                ) \n                         LineHueLast         (0         ).as(Real                ) \n                         LineSaturationLast  (0         ).as(Real                ) \n                         LineBrightnessLast  (0         ).as(Real                ) ] :Optional  :Contour Color GradientMode: HSB\n");
    fprintf(stderr, "    [-LineChange         LineColorChange     (0.1       ).as(Real                ) ] :Optional  :Contour Color Change\n");
    fprintf(stderr, "    [-LineWidthStart     LineWidthStart      (0.1       ).as(Real                ) ] :Optional  :Contour Line Width Step\n");
    fprintf(stderr, "    [-LineWidthStep      LineWidthStep       (0.05      ).as(Real                ) ] :Optional  :Contour Line Width Step\n");
    fprintf(stderr, "    [-ReverseOrder                                                                 ] :Optional  :Reverse Print Order\n");
    fprintf(stderr, "    [-Untwist            untwist             (0.0       ).as(Real                ) ] :Optional  :Untwist Angle [degree/A], example: (-13,28) = 0.4709576\n");
    fprintf(stderr, "    [-UpsideDown                                                                   ] :Optional  :Upside Down\n");
    fprintf(stderr, "    [-Centre                                                                       ] :Optional  :Image Centre is at the centre of paper.\n");
    fprintf(stderr, "    [-CircleRadius       CircleRadius        (0.5       ).as(Real                ) ] :Optional  :Radius of circles in the case of imageCircles\n");
    fprintf(stderr, "    [-m[ode]             mode                (49        ).as(Integer             ) ] :Optional  :Mode\n");
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
