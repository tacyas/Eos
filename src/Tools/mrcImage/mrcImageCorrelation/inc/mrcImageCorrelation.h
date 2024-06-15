#ifndef MRCIMAGECORRELATION_H
#define MRCIMAGECORRELATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCorrelationInfo {
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
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagOutCor;
    char* OutCor;
    FILE* fptOutCor;
    
    long flagAvg;
    char* Avg;
    FILE* fptAvg;
    
    long flagShift;
    char* Shift;
    FILE* fptShift;
    
    long flagRefineStep;
    float RefineStep;
    
    long flagRefineRange;
    float RefineRange;
    
    long flagRefineMode;
    long RefineMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagmode2;
    long mode2;
    
} mrcImageCorrelationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCorrelationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCorrelationInfo* info);
extern void init1(mrcImageCorrelationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECORRELATION_H */
