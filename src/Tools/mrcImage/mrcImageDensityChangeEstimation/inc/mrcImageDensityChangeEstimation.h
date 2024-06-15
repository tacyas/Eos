#ifndef MRCIMAGEDENSITYCHANGEESTIMATION_H
#define MRCIMAGEDENSITYCHANGEESTIMATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageDensityChangeEstimationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagIn2;
    char* In2;
    FILE* fptIn2;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageDensityChangeEstimationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageDensityChangeEstimationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageDensityChangeEstimationInfo* info);
extern void init1(mrcImageDensityChangeEstimationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEDENSITYCHANGEESTIMATION_H */
