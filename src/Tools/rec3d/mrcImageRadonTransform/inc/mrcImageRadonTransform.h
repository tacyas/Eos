#ifndef MRCIMAGERADONTRANSFORM_H
#define MRCIMAGERADONTRANSFORM_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageRadonTransformInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagdtheta;
    float dtheta;
    
    long flagdphi;
    float dphi;
    
    long flagmode;
    long mode;
    
} mrcImageRadonTransformInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageRadonTransformInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageRadonTransformInfo* info);
extern void init1(mrcImageRadonTransformInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGERADONTRANSFORM_H */
