#ifndef MRCIMAGEFILTERINGBYFILEFORVARIANCE_H
#define MRCIMAGEFILTERINGBYFILEFORVARIANCE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageFilteringbyFileForVarianceInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagFilter;
    char* Filter;
    FILE* fptFilter;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageFilteringbyFileForVarianceInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageFilteringbyFileForVarianceInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageFilteringbyFileForVarianceInfo* info);
extern void init1(mrcImageFilteringbyFileForVarianceInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEFILTERINGBYFILEFORVARIANCE_H */
