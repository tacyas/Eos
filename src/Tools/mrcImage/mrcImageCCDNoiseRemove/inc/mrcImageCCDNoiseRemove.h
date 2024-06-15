#ifndef MRCIMAGECCDNOISEREMOVE_H
#define MRCIMAGECCDNOISEREMOVE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCCDNoiseRemoveInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInNoise;
    char* InNoise;
    FILE* fptInNoise;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageCCDNoiseRemoveInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCCDNoiseRemoveInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCCDNoiseRemoveInfo* info);
extern void init1(mrcImageCCDNoiseRemoveInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECCDNOISEREMOVE_H */
