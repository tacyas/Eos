#ifndef MRCIMAGEMODECHANGE_H
#define MRCIMAGEMODECHANGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageModeChangeInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagMin;
    float Min;
    
    long flagMax;
    float Max;
    
    long flagStat;

    long flagSigned;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageModeChangeInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageModeChangeInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageModeChangeInfo* info);
extern void init1(mrcImageModeChangeInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMODECHANGE_H */
