#ifndef MRCIMAGESINOGRAMCORRELATION_H
#define MRCIMAGESINOGRAMCORRELATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSinogramCorrelationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagw0th;
    float w0th;
    
    long flagw1st;
    float w1st;
    
    long flagw2nd;
    float w2nd;
    
    long flagthreshold;
    float threshold;
    
    long flagcorMode;
    long corMode;
    
    long flagLengthMode;
    long LengthMode;
    
    long flagLengthThresholdMode;
    long LengthThresholdMode;
    
    long flagLengthThresholdRatio;
    float LengthThresholdRatio;
    
    long flagLCMode;
    long LCMode;
    
    long flagLengthCorrelationThreshold;
    float LengthCorrelationThreshold;
    
    long flagweightLength;
    float weightLength;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSinogramCorrelationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSinogramCorrelationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSinogramCorrelationInfo* info);
extern void init1(mrcImageSinogramCorrelationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESINOGRAMCORRELATION_H */
