#ifndef MRCIMAGEFEATUREEXTRACTION_H
#define MRCIMAGEFEATUREEXTRACTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageFeatureExtractionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagco_r;
    long co_r;
    
    long flagco_theta;
    long co_theta;
    
    long flagrl_theta;
    long rl_theta;
    
    long flagrl_dev;
    long rl_dev;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageFeatureExtractionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageFeatureExtractionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageFeatureExtractionInfo* info);
extern void init1(mrcImageFeatureExtractionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEFEATUREEXTRACTION_H */
