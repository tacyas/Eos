#ifndef MRCIMAGEBILATERALFILTER_H
#define MRCIMAGEBILATERALFILTER_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageBilateralFilterInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagSigmaDensity;
    float SigmaDensity;
    
    long flagKernelTypeDensity;
    long KernelTypeDensity;
    
    long flagSigmaSpace;
    float SigmaSpace;
    
    long flagSigmaSpaceX;
    float SigmaSpaceX;
    
    long flagSigmaSpaceY;
    float SigmaSpaceY;
    
    long flagSigmaSpaceZ;
    float SigmaSpaceZ;
    
    long flagKernelTypeSpace;
    long KernelTypeSpace;
    
    long flagKernelSize;
    long KernelSize;
    
    long flagKernelSizeX;
    long KernelSizeX;
    
    long flagKernelSizeY;
    long KernelSizeY;
    
    long flagKernelSizeZ;
    long KernelSizeZ;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageBilateralFilterInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageBilateralFilterInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageBilateralFilterInfo* info);
extern void init1(mrcImageBilateralFilterInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEBILATERALFILTER_H */
