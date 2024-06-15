#ifndef MRCIMAGESMOOTHING_H
#define MRCIMAGESMOOTHING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSmoothingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagsx;
    float sx;
    
    long flagsy;
    float sy;
    
    long flagsz;
    float sz;
    
    long flagr;
    float r;
    
    long flagsigma;
    float sigma;
    
    long flagtimes;
    long times;
    
    long flagmode;
    long mode;
    
    long flagmode2;
    long mode2;
    
    long verbose;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
} mrcImageSmoothingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSmoothingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSmoothingInfo* info);
extern void init1(mrcImageSmoothingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESMOOTHING_H */
