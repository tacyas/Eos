#ifndef MRCIMAGECTFCOMPENSATION_H
#define MRCIMAGECTFCOMPENSATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCTFCompensationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagkV;
    float kV;
    
    long flagCs;
    float Cs;
    
    long flagDefocus;
    float Defocus;
    
    long flagWhiteNoise;
    float WhiteNoise;
    
    long flagSinWinRmin;
    float SinWinRmin;
    
    long flagSinWinRmax;
    float SinWinRmax;
    
    long flagAmp;
    float Amp;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageCTFCompensationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCTFCompensationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCTFCompensationInfo* info);
extern void init1(mrcImageCTFCompensationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECTFCOMPENSATION_H */
