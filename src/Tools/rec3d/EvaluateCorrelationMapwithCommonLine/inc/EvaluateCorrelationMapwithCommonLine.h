#ifndef EVALUATECORRELATIONMAPWITHCOMMONLINE_H
#define EVALUATECORRELATIONMAPWITHCOMMONLINE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct EvaluateCorrelationMapwithCommonLineInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInC;
    char* InC;
    FILE* fptInC;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagPm;
    long Pm;
    
    long flagPN;
    long PN;
    
    long flagPDT;
    float PDT;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} EvaluateCorrelationMapwithCommonLineInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(EvaluateCorrelationMapwithCommonLineInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(EvaluateCorrelationMapwithCommonLineInfo* info);
extern void init1(EvaluateCorrelationMapwithCommonLineInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* EVALUATECORRELATIONMAPWITHCOMMONLINE_H */
