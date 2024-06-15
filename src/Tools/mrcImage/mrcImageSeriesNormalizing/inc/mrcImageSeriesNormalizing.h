#ifndef MRCIMAGESERIESNORMALIZING_H
#define MRCIMAGESERIESNORMALIZING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSeriesNormalizingInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagWeight;
    char* Weight;
    FILE* fptWeight;
    
    long flagOut;
    char** Out;
    char* OutList;
    FILE** fptOut;
    FILE* fptOutList;
    
    long flagParam;
    char* Param;
    FILE* fptParam;
    
    long flagthresOfLowValueArea;
    float thresOfLowValueArea;
    
    long flagthresOfHighValueArea;
    float thresOfHighValueArea;
    
    long flagLow;
    float Low;
    
    long flagHigh;
    float High;
    
    long flagUseLow;
    long UseLow;
    
    long flagUseHigh;
    long UseHigh;
    
    long flagALow;
    float ALow;
    
    long flagKLow;
    float KLow;
    
    long flagBLow;
    float BLow;
    
    long flagAHigh;
    float AHigh;
    
    long flagKHigh;
    float KHigh;
    
    long flagBHigh;
    float BHigh;
    
    long flagmaxIter;
    long maxIter;
    
    long flagxtol;
    float xtol;
    
    long flaggtol;
    float gtol;
    
    long flagftol;
    float ftol;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSeriesNormalizingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSeriesNormalizingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSeriesNormalizingInfo* info);
extern void init1(mrcImageSeriesNormalizingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESERIESNORMALIZING_H */
