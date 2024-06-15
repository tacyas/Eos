#ifndef MRCIMAGEHOUGHTRANSFORM_H
#define MRCIMAGEHOUGHTRANSFORM_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageHoughTransformInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagDeltaTheta;
    float DeltaTheta;
    
    long flagDeltaRho;
    float DeltaRho;
    
    long flagHoughMode;
    long HoughMode;
    
    long flagwidthMin;
    float widthMin;
    
    long flagwidthMax;
    long widthMax;
    
    long flagwidthOut;
    float widthOut;
    
    long flagInterpolationMode;
    long InterpolationMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageHoughTransformInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageHoughTransformInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageHoughTransformInfo* info);
extern void init1(mrcImageHoughTransformInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEHOUGHTRANSFORM_H */
