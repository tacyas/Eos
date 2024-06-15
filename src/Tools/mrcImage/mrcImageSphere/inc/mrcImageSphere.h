#ifndef MRCIMAGESPHERE_H
#define MRCIMAGESPHERE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSphereInfo {
    long flagRedirect;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagsize;
    float size;
    
    long flagr;
    float r;
    
    long flagw;
    float w;
    
    long flagmode;
    long mode;
    
} mrcImageSphereInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSphereInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSphereInfo* info);
extern void init1(mrcImageSphereInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESPHERE_H */
