#ifndef MRCIMAGECONVOLUTION_H
#define MRCIMAGECONVOLUTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageConvolutionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInKernelArray;
    char* InKernelArray;
    FILE* fptInKernelArray;
    
    long flagInKernelMRC;
    char* InKernelMRC;
    FILE* fptInKernelMRC;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagtimes;
    long times;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageConvolutionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageConvolutionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageConvolutionInfo* info);
extern void init1(mrcImageConvolutionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECONVOLUTION_H */
