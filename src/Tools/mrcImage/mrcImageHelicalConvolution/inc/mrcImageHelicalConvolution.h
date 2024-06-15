#ifndef MRCIMAGEHELICALCONVOLUTION_H
#define MRCIMAGEHELICALCONVOLUTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageHelicalConvolutionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagdelPhi;
    float delPhi;
    
    long flagdelZ;
    float delZ;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagNz;
    long Nz;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageHelicalConvolutionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageHelicalConvolutionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageHelicalConvolutionInfo* info);
extern void init1(mrcImageHelicalConvolutionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEHELICALCONVOLUTION_H */
