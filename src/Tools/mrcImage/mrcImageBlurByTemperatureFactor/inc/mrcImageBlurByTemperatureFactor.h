#ifndef MRCIMAGEBLURBYTEMPERATUREFACTOR_H
#define MRCIMAGEBLURBYTEMPERATUREFACTOR_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageBlurByTemperatureFactorInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInCoord;
    char* InCoord;
    FILE* fptInCoord;
    
    long flagType;
    long Type;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageBlurByTemperatureFactorInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageBlurByTemperatureFactorInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageBlurByTemperatureFactorInfo* info);
extern void init1(mrcImageBlurByTemperatureFactorInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEBLURBYTEMPERATUREFACTOR_H */
