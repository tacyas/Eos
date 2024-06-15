#ifndef CTFWEIGHTMAPCREATION_H
#define CTFWEIGHTMAPCREATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ctfWeightMapCreationInfo {
    long flagRedirect;

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
    
    long flagNoise;
    char* Noise;
    FILE* fptNoise;
    
    long flagSplusN;
    char* SplusN;
    FILE* fptSplusN;
    
    long flagdRinv;
    float dRinv;
    
    long flagdRmaxInv;
    float dRmaxInv;
    
    long flagSinWinRminInv;
    float SinWinRminInv;
    
    long flagSinWinRmaxInv;
    float SinWinRmaxInv;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} ctfWeightMapCreationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ctfWeightMapCreationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ctfWeightMapCreationInfo* info);
extern void init1(ctfWeightMapCreationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CTFWEIGHTMAPCREATION_H */
