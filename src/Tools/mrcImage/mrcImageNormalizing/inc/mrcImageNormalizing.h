#ifndef MRCIMAGENORMALIZING_H
#define MRCIMAGENORMALIZING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageNormalizingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagA;
    float A;
    
    long flagB;
    float B;
    
    long flagContourMin;
    float ContourMin;
    
    long flagContourMax;
    float ContourMax;
    
    long flagContourSolvent;
    float ContourSolvent;
    
    long flagthresOfLowValueArea;
    float thresOfLowValueArea;
    
    long flagthresOfHighValueArea;
    float thresOfHighValueArea;
    
    long flagParamOut;
    char* ParamOut;
    FILE* fptParamOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageNormalizingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageNormalizingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageNormalizingInfo* info);
extern void init1(mrcImageNormalizingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGENORMALIZING_H */
