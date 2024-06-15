#ifndef MRCIMAGEBINALIZATION_H
#define MRCIMAGEBINALIZATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageBinalizationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutParam;
    char* OutParam;
    FILE* fptOutParam;
    
    long flagt;
    float t;
    
    long flagdeltaThreshold;
    float deltaThreshold;
    
    long flagsigmaThreshold;
    float sigmaThreshold;
    
    long flagv;
    float v;
    
    long flagnear;
    float near;
    
    long flagnLevel;
    long nLevel;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagp;
    float p;
    
    long flagmode;
    long mode;
    
} mrcImageBinalizationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageBinalizationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageBinalizationInfo* info);
extern void init1(mrcImageBinalizationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEBINALIZATION_H */
