#ifndef MRCIMAGEGRADIENT_H
#define MRCIMAGEGRADIENT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageGradientInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutDx;
    char* OutDx;
    FILE* fptOutDx;
    
    long flagOutDy;
    char* OutDy;
    FILE* fptOutDy;
    
    long flagOutDz;
    char* OutDz;
    FILE* fptOutDz;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageGradientInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageGradientInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageGradientInfo* info);
extern void init1(mrcImageGradientInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEGRADIENT_H */
