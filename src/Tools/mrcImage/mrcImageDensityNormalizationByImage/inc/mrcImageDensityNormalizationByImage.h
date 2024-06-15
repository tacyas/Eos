#ifndef MRCIMAGEDENSITYNORMALIZATIONBYIMAGE_H
#define MRCIMAGEDENSITYNORMALIZATIONBYIMAGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageDensityNormalizationByImageInfo {
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
    
    long flagOutParam;
    char* OutParam;
    FILE* fptOutParam;
    
    long flagUsedData;
    char* UsedData;
    FILE* fptUsedData;
    
    long flagCCenterX;
    float CCenterX;
    
    long flagCCenterY;
    float CCenterY;
    
    long flagCMinR;
    float CMinR;
    
    long flagCMaxR;
    float CMaxR;
    
    long flagtstBGMin;
    float tstBGMin;
    
    long flagtstBGMax;
    float tstBGMax;
    
    long flagtstBGDelta;
    float tstBGDelta;
    
    long flagfitMode;
    long fitMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageDensityNormalizationByImageInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageDensityNormalizationByImageInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageDensityNormalizationByImageInfo* info);
extern void init1(mrcImageDensityNormalizationByImageInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEDENSITYNORMALIZATIONBYIMAGE_H */
