#ifndef MRCIMAGE3DPAD_H
#define MRCIMAGE3DPAD_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImage3DPadInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagr;
    float r;
    
    long flagw;
    float w;
    
    long flagv;
    float v;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagNz;
    long Nz;
    
    long Floating;

    long flagmode;
    long mode;
    
    long flagmode2;
    long mode2;
    
} mrcImage3DPadInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImage3DPadInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImage3DPadInfo* info);
extern void init1(mrcImage3DPadInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGE3DPAD_H */
