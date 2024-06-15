#ifndef MRCIMAGERANDOMPARTICLESIMAGECREATE_H
#define MRCIMAGERANDOMPARTICLESIMAGECREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageRandomParticlesImageCreateInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagSeed;
    long Seed;
    
    long flagInterpolationMode;
    long InterpolationMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageRandomParticlesImageCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageRandomParticlesImageCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageRandomParticlesImageCreateInfo* info);
extern void init1(mrcImageRandomParticlesImageCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGERANDOMPARTICLESIMAGECREATE_H */
