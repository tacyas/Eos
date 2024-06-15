#ifndef MRC2BILD_H
#define MRC2BILD_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrc2bildInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagIn0;
    char* In0;
    FILE* fptIn0;
    
    long flagIn1;
    char* In1;
    FILE* fptIn1;
    
    long flagIn2;
    char* In2;
    FILE* fptIn2;
    
    long flagInX;
    char* InX;
    FILE* fptInX;
    
    long flagInY;
    char* InY;
    FILE* fptInY;
    
    long flagInZ;
    char* InZ;
    FILE* fptInZ;
    
    long flagInWeight;
    char* InWeight;
    FILE* fptInWeight;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRed;
    float Red;
    
    long flagGreen;
    float Green;
    
    long flagBlue;
    float Blue;
    
    long flagZoom;
    float Zoom;
    
    long flagR1;
    float R1;
    
    long flagR2;
    float R2;
    
    long flagRho;
    float Rho;
    
    long flagskipX;
    long skipX;
    
    long flagskipY;
    long skipY;
    
    long flagskipZ;
    long skipZ;
    
    long flagRainbowMode;
    long RainbowMode;
    
    long flagRainbowThresLow;
    float RainbowThresLow;
    
    long flagRainbowThresHigh;
    float RainbowThresHigh;
    
    long flagRainbowRangeLow;
    float RainbowRangeLow;
    
    long flagRainbowRangeHigh;
    float RainbowRangeHigh;
    
    long flagRangeXMin;
    float RangeXMin;
    
    long flagRangeXMax;
    float RangeXMax;
    
    long flagRangeYMin;
    float RangeYMin;
    
    long flagRangeYMax;
    float RangeYMax;
    
    long flagRangeZMin;
    float RangeZMin;
    
    long flagRangeZMax;
    float RangeZMax;
    
    long flagRangeRCX;
    float RangeRCX;
    
    long flagRangeRCY;
    float RangeRCY;
    
    long flagRangeRCZ;
    float RangeRCZ;
    
    long flagRangeRR;
    float RangeRR;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrc2bildInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrc2bildInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrc2bildInfo* info);
extern void init1(mrc2bildInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRC2BILD_H */
