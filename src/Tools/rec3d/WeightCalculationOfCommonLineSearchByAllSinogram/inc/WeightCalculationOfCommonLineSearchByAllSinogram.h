#ifndef WEIGHTCALCULATIONOFCOMMONLINESEARCHBYALLSINOGRAM_H
#define WEIGHTCALCULATIONOFCOMMONLINESEARCHBYALLSINOGRAM_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct WeightCalculationOfCommonLineSearchByAllSinogramInfo {
    long flagRedirect;

    long flagIn1;
    char** In1;
    char* In1List;
    FILE** fptIn1;
    FILE* fptIn1List;
    
    long flagIn2;
    char** In2;
    char* In2List;
    FILE** fptIn2;
    FILE* fptIn2List;
    
    long flagIn3;
    char** In3;
    char* In3List;
    FILE** fptIn3;
    FILE* fptIn3List;
    
    long flagIn4;
    char** In4;
    char* In4List;
    FILE** fptIn4;
    FILE* fptIn4List;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagMode;
    long Mode;
    
    long flagvariance;
    float variance;
    
} WeightCalculationOfCommonLineSearchByAllSinogramInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(WeightCalculationOfCommonLineSearchByAllSinogramInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(WeightCalculationOfCommonLineSearchByAllSinogramInfo* info);
extern void init1(WeightCalculationOfCommonLineSearchByAllSinogramInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* WEIGHTCALCULATIONOFCOMMONLINESEARCHBYALLSINOGRAM_H */
