#ifndef MRCIMAGEHELICALAVERAGING_H
#define MRCIMAGEHELICALAVERAGING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageHelicalAveragingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagdz;
    float dz;
    
    long flagdp;
    float dp;
    
    long flagN;
    long N;
    
    long flagW;
    long W;
    
    long flagmode;
    long mode;
    
} mrcImageHelicalAveragingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageHelicalAveragingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageHelicalAveragingInfo* info);
extern void init1(mrcImageHelicalAveragingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEHELICALAVERAGING_H */
