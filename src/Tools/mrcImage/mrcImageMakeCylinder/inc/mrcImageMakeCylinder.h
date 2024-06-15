#ifndef MRCIMAGEMAKECYLINDER_H
#define MRCIMAGEMAKECYLINDER_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageMakeCylinderInfo {
    long flagRedirect;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagResolution;
    float Resolution;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageMakeCylinderInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageMakeCylinderInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageMakeCylinderInfo* info);
extern void init1(mrcImageMakeCylinderInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMAKECYLINDER_H */
