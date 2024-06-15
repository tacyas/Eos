#ifndef MRCIMAGESAMPLINGUNITCHANGE_H
#define MRCIMAGESAMPLINGUNITCHANGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSamplingUnitChangeInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagSx;
    float Sx;
    
    long flagSy;
    float Sy;
    
    long flagSz;
    float Sz;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagNz;
    float Nz;
    
    long flagRatio;
    float Ratio;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSamplingUnitChangeInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSamplingUnitChangeInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSamplingUnitChangeInfo* info);
extern void init1(mrcImageSamplingUnitChangeInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESAMPLINGUNITCHANGE_H */
