#ifndef MRCIMAGE2DPROJECTION_H
#define MRCIMAGE2DPROJECTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImage2DProjectionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOmega;
    float Omega;
    
    long flagPhi;
    float Phi;
    
    long flagAlpha;
    float Alpha;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImage2DProjectionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImage2DProjectionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImage2DProjectionInfo* info);
extern void init1(mrcImage2DProjectionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGE2DPROJECTION_H */
