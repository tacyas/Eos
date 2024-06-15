#ifndef MRCIMAGEDENSITYWEIGHTEDAREACALC_H
#define MRCIMAGEDENSITYWEIGHTEDAREACALC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageDensityWeightedAreaCalcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInDensity;
    char* InDensity;
    FILE* fptInDensity;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutLabel;
    char* OutLabel;
    FILE* fptOutLabel;
    
    long flagNeighbor;
    long Neighbor;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageDensityWeightedAreaCalcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageDensityWeightedAreaCalcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageDensityWeightedAreaCalcInfo* info);
extern void init1(mrcImageDensityWeightedAreaCalcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEDENSITYWEIGHTEDAREACALC_H */
