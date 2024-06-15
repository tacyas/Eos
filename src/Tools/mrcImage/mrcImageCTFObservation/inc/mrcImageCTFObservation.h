#ifndef MRCIMAGECTFOBSERVATION_H
#define MRCIMAGECTFOBSERVATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCTFObservationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagCTF;
    char* CTF;
    FILE* fptCTF;
    
    long flagkV;
    float kV;
    
    long flagCs;
    float Cs;
    
    long flagDefocus;
    float Defocus;
    
    long flagAoverP;
    float AoverP;
    
    long flagAin;
    float Ain;
    
    long flagWhiteNoise;
    float WhiteNoise;
    
    long flagSinWinRmin;
    float SinWinRmin;
    
    long flagSinWinRmax;
    float SinWinRmax;
    
    long flagctfMode;
    long ctfMode;
    
    long flagdfMin;
    float dfMin;
    
    long flagdfMax;
    float dfMax;
    
    long flagasAxis;
    float asAxis;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageCTFObservationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCTFObservationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCTFObservationInfo* info);
extern void init1(mrcImageCTFObservationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECTFOBSERVATION_H */
