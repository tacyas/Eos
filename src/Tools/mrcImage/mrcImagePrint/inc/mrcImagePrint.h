#ifndef MRCIMAGEPRINT_H
#define MRCIMAGEPRINT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImagePrintInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagthresHigh;
    float thresHigh;
    
    long flagthresLow;
    float thresLow;
    
    long flagsection;
    char  section;
    
    long flagxMin;
    long xMin;
    
    long flagxMax;
    long xMax;
    
    long flagyMin;
    long yMin;
    
    long flagyMax;
    long yMax;
    
    long flagzMin;
    long zMin;
    
    long flagzMax;
    long zMax;
    
    long flagScale;
    float Scale;
    
    long flagAbScale;
    float AbScale;
    
    long flagEnlarge;
    float Enlarge;
    
    long flagcx;
    float cx;
    
    long flagcy;
    float cy;
    
    long flagcontourLevel;
    float* contourLevel;
    
    long Inverse;

    long Auto;

    long flagAutoContour;
    long AutoContour;
    
    long flagPeakContour;
    long PeakContour;
    
    long flagAutoContour2;
    long AutoContour2;
    
    long flagYexpand;
    float Yexpand;
    
    long flagRed;
    float Red;
    
    long flagGreen;
    float Green;
    
    long flagBlue;
    float Blue;
    
    long flagRedFirst;
    float RedFirst;
    
    long flagGreenFirst;
    float GreenFirst;
    
    long flagBlueFirst;
    float BlueFirst;
    
    long flagRedLast;
    float RedLast;
    
    long flagGreenLast;
    float GreenLast;
    
    long flagBlueLast;
    float BlueLast;
    
    long flagHue;
    float Hue;
    
    long flagSaturation;
    float Saturation;
    
    long flagBrightness;
    float Brightness;
    
    long flagHueFirst;
    float HueFirst;
    
    long flagSaturationFirst;
    float SaturationFirst;
    
    long flagBrightnessFirst;
    float BrightnessFirst;
    
    long flagHueLast;
    float HueLast;
    
    long flagSaturationLast;
    float SaturationLast;
    
    long flagBrightnessLast;
    float BrightnessLast;
    
    long flagLineRed;
    float LineRed;
    
    long flagLineGreen;
    float LineGreen;
    
    long flagLineBlue;
    float LineBlue;
    
    long flagLineRedFirst;
    float LineRedFirst;
    
    long flagLineGreenFirst;
    float LineGreenFirst;
    
    long flagLineBlueFirst;
    float LineBlueFirst;
    
    long flagLineRedLast;
    float LineRedLast;
    
    long flagLineGreenLast;
    float LineGreenLast;
    
    long flagLineBlueLast;
    float LineBlueLast;
    
    long flagLineHue;
    float LineHue;
    
    long flagLineSaturation;
    float LineSaturation;
    
    long flagLineBrightness;
    float LineBrightness;
    
    long flagLineHueFirst;
    float LineHueFirst;
    
    long flagLineSaturationFirst;
    float LineSaturationFirst;
    
    long flagLineBrightnessFirst;
    float LineBrightnessFirst;
    
    long flagLineHueLast;
    float LineHueLast;
    
    long flagLineSaturationLast;
    float LineSaturationLast;
    
    long flagLineBrightnessLast;
    float LineBrightnessLast;
    
    long flagLineColorChange;
    float LineColorChange;
    
    long flagLineWidthStart;
    float LineWidthStart;
    
    long flagLineWidthStep;
    float LineWidthStep;
    
    long ReverseOrder;

    long flaguntwist;
    float untwist;
    
    long UpsideDown;

    long Centre;

    long flagCircleRadius;
    float CircleRadius;
    
    long flagmode;
    long mode;
    
} mrcImagePrintInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImagePrintInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImagePrintInfo* info);
extern void init1(mrcImagePrintInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEPRINT_H */
