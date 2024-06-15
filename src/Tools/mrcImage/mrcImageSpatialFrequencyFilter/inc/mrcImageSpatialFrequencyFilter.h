#ifndef MRCIMAGESPATIALFREQUENCYFILTER_H
#define MRCIMAGESPATIALFREQUENCYFILTER_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSpatialFrequencyFilterInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagfilterIn;
    char* filterIn;
    FILE* fptfilterIn;
    
    long flagcolR;
    long colR;
    
    long flagcolW;
    long colW;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagLow;
    float Low;
    
    long flagHigh;
    float High;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSpatialFrequencyFilterInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSpatialFrequencyFilterInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSpatialFrequencyFilterInfo* info);
extern void init1(mrcImageSpatialFrequencyFilterInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESPATIALFREQUENCYFILTER_H */
