#ifndef MRCIMAGE1DAVERAGEBYCORRELATION_H
#define MRCIMAGE1DAVERAGEBYCORRELATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImage1dAverageByCorrelationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagrange;
    long range;
    
    long flagSignal;
    char* Signal;
    FILE* fptSignal;
    
    long flagdelta;
    float delta;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImage1dAverageByCorrelationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImage1dAverageByCorrelationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImage1dAverageByCorrelationInfo* info);
extern void init1(mrcImage1dAverageByCorrelationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGE1DAVERAGEBYCORRELATION_H */
