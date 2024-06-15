#ifndef MRCIMAGEPUT3D_H
#define MRCIMAGEPUT3D_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImagePut3DInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long Stereo;

    long flagContour;
    float Contour;
    
    long flagxLight;
    float xLight;
    
    long flagyLight;
    float yLight;
    
    long flagzLight;
    float zLight;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImagePut3DInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImagePut3DInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImagePut3DInfo* info);
extern void init1(mrcImagePut3DInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEPUT3D_H */
