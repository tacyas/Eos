#ifndef CTFDETERMINATIONFROMTHONRING_H
#define CTFDETERMINATIONFROMTHONRING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ctfDeterminationFromThonRingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut2;
    char* Out2;
    FILE* fptOut2;
    
    long flagkV;
    float kV;
    
    long flagCs;
    float Cs;
    
    long flagminDef;
    float minDef;
    
    long flagmaxDef;
    float maxDef;
    
    long flagdelDef;
    float delDef;
    
    long flagminAmp;
    float minAmp;
    
    long flagmaxAmp;
    float maxAmp;
    
    long flagdelAmp;
    float delAmp;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagR;
    float* R;
    
} ctfDeterminationFromThonRingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ctfDeterminationFromThonRingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ctfDeterminationFromThonRingInfo* info);
extern void init1(ctfDeterminationFromThonRingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CTFDETERMINATIONFROMTHONRING_H */
