#ifndef MRCIMAGEMONTAGECREATE_H
#define MRCIMAGEMONTAGECREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageMontageCreateInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagWidth;
    long Width;
    
    long flagHeight;
    long Height;
    
    long flagAvgWnd;
    float AvgWnd;
    
    long flagValue;
    float Value;
    
    long flagPadMode;
    long PadMode;
    
    long EdgeAverage;

    long flagEdgeAverageWindow;
    long EdgeAverageWindow;
    
    long NoAverage;

    long flagMax;
    float Max;
    
    long flagVMax;
    float VMax;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageMontageCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageMontageCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageMontageCreateInfo* info);
extern void init1(mrcImageMontageCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMONTAGECREATE_H */
