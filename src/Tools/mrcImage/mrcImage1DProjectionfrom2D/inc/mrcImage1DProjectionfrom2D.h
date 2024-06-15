#ifndef MRCIMAGE1DPROJECTIONFROM2D_H
#define MRCIMAGE1DPROJECTIONFROM2D_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImage1DProjectionfrom2DInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagphi;
    float phi;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImage1DProjectionfrom2DInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImage1DProjectionfrom2DInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImage1DProjectionfrom2DInfo* info);
extern void init1(mrcImage1DProjectionfrom2DInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGE1DPROJECTIONFROM2D_H */
