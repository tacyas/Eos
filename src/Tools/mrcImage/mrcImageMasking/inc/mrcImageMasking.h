#ifndef MRCIMAGEMASKING_H
#define MRCIMAGEMASKING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageMaskingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagnx;
    float nx;
    
    long flagny;
    float ny;
    
    long flagnz;
    float nz;
    
    long flagcx;
    float cx;
    
    long flagcy;
    float cy;
    
    long flagcz;
    float cz;
    
    long flagEuler;
    char* Euler;
    
    long flagRot1;
    float Rot1;
    
    long flagRot2;
    float Rot2;
    
    long flagRot3;
    float Rot3;
    
    long flagShape;
    long Shape;
    
    long flagSoft;
    long Soft;
    
    long flagSoftWidth;
    float SoftWidth;
    
    long flagNormalize;
    long Normalize;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageMaskingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageMaskingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageMaskingInfo* info);
extern void init1(mrcImageMaskingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMASKING_H */
