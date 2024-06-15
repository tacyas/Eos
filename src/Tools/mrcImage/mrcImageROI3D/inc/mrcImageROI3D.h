#ifndef MRCIMAGEROI3D_H
#define MRCIMAGEROI3D_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageROI3DInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagx1;
    float x1;
    
    long flagx2;
    float x2;
    
    long flagy1;
    float y1;
    
    long flagy2;
    float y2;
    
    long flagz1;
    float z1;
    
    long flagz2;
    float z2;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageROI3DInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageROI3DInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageROI3DInfo* info);
extern void init1(mrcImageROI3DInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEROI3D_H */
