#ifndef MRCIMAGEMAKE2DARRAYIMAGE_H
#define MRCIMAGEMAKE2DARRAYIMAGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageMake2DArrayImageInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagNx;
    long Nx;
    
    long flagw;
    long w;
    
    long flagv;
    float v;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageMake2DArrayImageInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageMake2DArrayImageInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageMake2DArrayImageInfo* info);
extern void init1(mrcImageMake2DArrayImageInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMAKE2DARRAYIMAGE_H */
