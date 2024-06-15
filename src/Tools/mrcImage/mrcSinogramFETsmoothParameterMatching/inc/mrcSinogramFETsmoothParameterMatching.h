#ifndef MRCSINOGRAMFETSMOOTHPARAMETERMATCHING_H
#define MRCSINOGRAMFETSMOOTHPARAMETERMATCHING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcSinogramFETsmoothParameterMatchingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInSTD;
    char* InSTD;
    FILE* fptInSTD;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcSinogramFETsmoothParameterMatchingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcSinogramFETsmoothParameterMatchingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcSinogramFETsmoothParameterMatchingInfo* info);
extern void init1(mrcSinogramFETsmoothParameterMatchingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCSINOGRAMFETSMOOTHPARAMETERMATCHING_H */
