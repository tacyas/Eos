#ifndef MRCIMAGEROTATION3D_H
#define MRCIMAGEROTATION3D_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageRotation3DInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagEulerAngle;
    char* EulerAngle;
    
    long flagRot1;
    float Rot1;
    
    long flagRot2;
    float Rot2;
    
    long flagRot3;
    float Rot3;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagNz;
    long Nz;
    
    long flagMode;
    long Mode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageRotation3DInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageRotation3DInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageRotation3DInfo* info);
extern void init1(mrcImageRotation3DInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEROTATION3D_H */
