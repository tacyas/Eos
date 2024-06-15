#ifndef MRCIMAGEDECONVOLUTION_H
#define MRCIMAGEDECONVOLUTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageDeconvolutionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagKernel;
    char* Kernel;
    FILE* fptKernel;
    
    long flagKernelCentre;
    long KernelCentre;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutConv;
    char* OutConv;
    FILE* fptOutConv;
    
    long flagOutASCII;
    char* OutASCII;
    FILE* fptOutASCII;
    
    long flagOutRMSD;
    char* OutRMSD;
    FILE* fptOutRMSD;
    
    long flagthresCTF;
    float thresCTF;
    
    long flagNSRatio;
    float NSRatio;
    
    long flagNSCoeff;
    float NSCoeff;
    
    long flagPad3DMode;
    long Pad3DMode;
    
    long flagr;
    float r;
    
    long flagw;
    float w;
    
    long flagv;
    float v;
    
    long Floating;

    long flagmaxIter;
    long maxIter;
    
    long flagminRMSD;
    float minRMSD;
    
    long flaglambda;
    float lambda;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageDeconvolutionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageDeconvolutionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageDeconvolutionInfo* info);
extern void init1(mrcImageDeconvolutionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEDECONVOLUTION_H */
