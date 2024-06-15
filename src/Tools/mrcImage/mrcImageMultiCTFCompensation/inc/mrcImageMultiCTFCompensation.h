#ifndef MRCIMAGEMULTICTFCOMPENSATION_H
#define MRCIMAGEMULTICTFCOMPENSATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageMultiCTFCompensationInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagCTF;
    char** CTF;
    char* CTFList;
    FILE** fptCTF;
    FILE* fptCTFList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagfftOut;
    char* fftOut;
    FILE* fptfftOut;
    
    long flagWhiteNoise;
    float WhiteNoise;
    
    long flagWhiteNoiseRaising;
    float WhiteNoiseRaising;
    
    long flagMaxWhiteNoise;
    float MaxWhiteNoise;
    
    long flagNdependentWhiteNoise;
    long NdependentWhiteNoise;
    
    long flagSinWinRmin;
    float SinWinRmin;
    
    long flagSinWinRmax;
    float SinWinRmax;
    
    long flagMaxIter;
    long MaxIter;
    
    long flagCTFMode;
    long CTFMode;
    
    long flagsolventMode;
    float solventMode;
    
    long flagsolventSTD;
    float solventSTD;
    
    long flagLog;
    char* Log;
    FILE* fptLog;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageMultiCTFCompensationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageMultiCTFCompensationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageMultiCTFCompensationInfo* info);
extern void init1(mrcImageMultiCTFCompensationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMULTICTFCOMPENSATION_H */
