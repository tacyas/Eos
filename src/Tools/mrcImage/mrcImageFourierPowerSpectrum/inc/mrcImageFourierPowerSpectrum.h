#ifndef MRCIMAGEFOURIERPOWERSPECTRUM_H
#define MRCIMAGEFOURIERPOWERSPECTRUM_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageFourierPowerSpectrumInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagdX;
    float dX;
    
    long flagdY;
    float dY;
    
    long flagdZ;
    float dZ;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageFourierPowerSpectrumInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageFourierPowerSpectrumInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageFourierPowerSpectrumInfo* info);
extern void init1(mrcImageFourierPowerSpectrumInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEFOURIERPOWERSPECTRUM_H */
