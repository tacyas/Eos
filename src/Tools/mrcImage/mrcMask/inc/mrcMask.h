#ifndef MRCMASK_H
#define MRCMASK_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcMaskInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagsizeX;
    long sizeX;
    
    long flagsizeY;
    long sizeY;
    
    long flagv1x;
    float v1x;
    
    long flagv1y;
    float v1y;
    
    long flagv2x;
    float v2x;
    
    long flagv2y;
    float v2y;
    
    long flaginum;
    long inum;
    
    long flagnum;
    long num;
    
    long flagexnum;
    long exnum;
    
    long flagmode;
    long mode;
    
} mrcMaskInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcMaskInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcMaskInfo* info);
extern void init1(mrcMaskInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCMASK_H */
