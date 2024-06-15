#ifndef MRCFFTPLAINREDUCE_H
#define MRCFFTPLAINREDUCE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcFFTplainreduceInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagPos;
    long Pos;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagValue;
    float Value;
    
} mrcFFTplainreduceInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcFFTplainreduceInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcFFTplainreduceInfo* info);
extern void init1(mrcFFTplainreduceInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCFFTPLAINREDUCE_H */
