#ifndef CTFDETERMINATIONFROMPHASECOMPARISON_H
#define CTFDETERMINATIONFROMPHASECOMPARISON_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ctfDeterminationFromPhaseComparisonInfo {
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
    
    long flagkV;
    float kV;
    
    long flagCs;
    float Cs;
    
    long flagmindf;
    float mindf;
    
    long flagmaxdf;
    float maxdf;
    
    long flagdeldf;
    float deldf;
    
    long flagminAoverP;
    float minAoverP;
    
    long flagmaxAoverP;
    float maxAoverP;
    
    long flagdelAoverP;
    float delAoverP;
    
    long flagRmax;
    float Rmax;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} ctfDeterminationFromPhaseComparisonInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ctfDeterminationFromPhaseComparisonInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ctfDeterminationFromPhaseComparisonInfo* info);
extern void init1(ctfDeterminationFromPhaseComparisonInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CTFDETERMINATIONFROMPHASECOMPARISON_H */
