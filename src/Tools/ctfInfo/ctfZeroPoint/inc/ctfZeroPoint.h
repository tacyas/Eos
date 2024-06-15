#ifndef CTFZEROPOINT_H
#define CTFZEROPOINT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ctfZeroPointInfo {
    long flagRedirect;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRMax;
    float RMax;
    
    long flagdR;
    float dR;
    
    long flagkV;
    float kV;
    
    long flagCs;
    float Cs;
    
    long flagDefocus;
    float Defocus;
    
    long flagMinDefocus;
    float MinDefocus;
    
    long flagMaxDefocus;
    float MaxDefocus;
    
    long flagDeltaDefocus;
    float DeltaDefocus;
    
    long flagAoverP;
    float AoverP;
    
    long flagN;
    long N;
    
    long flagAin;
    float Ain;
    
    long flagctfMode;
    long ctfMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} ctfZeroPointInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ctfZeroPointInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ctfZeroPointInfo* info);
extern void init1(ctfZeroPointInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CTFZEROPOINT_H */
