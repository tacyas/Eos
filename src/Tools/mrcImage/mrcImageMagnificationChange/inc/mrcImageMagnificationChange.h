#ifndef MRCIMAGEMAGNIFICATIONCHANGE_H
#define MRCIMAGEMAGNIFICATIONCHANGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageMagnificationChangeInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRatio;
    float Ratio;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageMagnificationChangeInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageMagnificationChangeInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageMagnificationChangeInfo* info);
extern void init1(mrcImageMagnificationChangeInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMAGNIFICATIONCHANGE_H */
