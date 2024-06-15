#ifndef MRCIMAGEPRINT3D_H
#define MRCIMAGEPRINT3D_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImagePrint3DInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flageyeX;
    float eyeX;
    
    long flageyeY;
    float eyeY;
    
    long flageyeZ;
    float eyeZ;
    
    long flagplaneX;
    float planeX;
    
    long flagplaneY;
    float planeY;
    
    long flagplaneZ;
    float planeZ;
    
    long flagcontourLevel;
    float* contourLevel;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImagePrint3DInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImagePrint3DInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImagePrint3DInfo* info);
extern void init1(mrcImagePrint3DInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEPRINT3D_H */
