#ifndef MRCIMAGEMODELSUBFILAMENTSCREATE_H
#define MRCIMAGEMODELSUBFILAMENTSCREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageModelSubfilamentsCreateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagnx;
    long nx;
    
    long flagny;
    long ny;
    
    long flagnz;
    long nz;
    
    long flaglx;
    float lx;
    
    long flagly;
    float ly;
    
    long flaglz;
    float lz;
    
    long flagposition;
    float position;
    
    long flagnHelix;
    long nHelix;
    
    long flagdeltaPhi;
    float deltaPhi;
    
    long flagstartPhi;
    float startPhi;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageModelSubfilamentsCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageModelSubfilamentsCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageModelSubfilamentsCreateInfo* info);
extern void init1(mrcImageModelSubfilamentsCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMODELSUBFILAMENTSCREATE_H */
