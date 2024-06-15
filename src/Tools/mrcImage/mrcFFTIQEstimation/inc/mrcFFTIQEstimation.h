#ifndef MRCFFTIQESTIMATION_H
#define MRCFFTIQESTIMATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcFFTIQEstimationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagSpotList;
    char* SpotList;
    FILE* fptSpotList;
    
    long flagradius;
    long radius;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcFFTIQEstimationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcFFTIQEstimationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcFFTIQEstimationInfo* info);
extern void init1(mrcFFTIQEstimationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCFFTIQESTIMATION_H */
