#ifndef MRCIMAGEMULTICTFDETERMINATION_H
#define MRCIMAGEMULTICTFDETERMINATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageMultiCTFDeterminationInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
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
    
} mrcImageMultiCTFDeterminationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageMultiCTFDeterminationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageMultiCTFDeterminationInfo* info);
extern void init1(mrcImageMultiCTFDeterminationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMULTICTFDETERMINATION_H */
