#ifndef MRCIMAGEHOUGHTRANSFORMINVERSE_H
#define MRCIMAGEHOUGHTRANSFORMINVERSE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageHoughTransformInverseInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagdelta;
    long delta;
    
    long flagHoughSpaceMode;
    long HoughSpaceMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageHoughTransformInverseInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageHoughTransformInverseInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageHoughTransformInverseInfo* info);
extern void init1(mrcImageHoughTransformInverseInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEHOUGHTRANSFORMINVERSE_H */
