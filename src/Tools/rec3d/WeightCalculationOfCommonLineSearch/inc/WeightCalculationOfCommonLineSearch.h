#ifndef WEIGHTCALCULATIONOFCOMMONLINESEARCH_H
#define WEIGHTCALCULATIONOFCOMMONLINESEARCH_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct WeightCalculationOfCommonLineSearchInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagLengthThresholdMode;
    long LengthThresholdMode;
    
    long flagLengthThresholdRatio;
    float LengthThresholdRatio;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} WeightCalculationOfCommonLineSearchInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(WeightCalculationOfCommonLineSearchInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(WeightCalculationOfCommonLineSearchInfo* info);
extern void init1(WeightCalculationOfCommonLineSearchInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* WEIGHTCALCULATIONOFCOMMONLINESEARCH_H */
