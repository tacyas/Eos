#ifndef MRCIMAGEFEATURECALC_H
#define MRCIMAGEFEATURECALC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageFeatureCalcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutGC;
    char* OutGC;
    FILE* fptOutGC;
    
    long flagOutLabel;
    char* OutLabel;
    FILE* fptOutLabel;
    
    long flagOutPerimeter;
    char* OutPerimeter;
    FILE* fptOutPerimeter;
    
    long flagOutChain;
    char* OutChain;
    FILE* fptOutChain;
    
    long flagOutSurfaceArea;
    char* OutSurfaceArea;
    FILE* fptOutSurfaceArea;
    
    long flagOutDensityWeightedArea;
    char* OutDensityWeightedArea;
    FILE* fptOutDensityWeightedArea;
    
    long flagneighbor;
    long neighbor;
    
    long flagInDensity;
    char* InDensity;
    FILE* fptInDensity;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageFeatureCalcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageFeatureCalcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageFeatureCalcInfo* info);
extern void init1(mrcImageFeatureCalcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEFEATURECALC_H */
