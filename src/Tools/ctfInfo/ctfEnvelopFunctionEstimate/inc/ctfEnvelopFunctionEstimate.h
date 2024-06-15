#ifndef CTFENVELOPFUNCTIONESTIMATE_H
#define CTFENVELOPFUNCTIONESTIMATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ctfEnvelopFunctionEstimateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagdegree;
    long degree;
    
    long flagCutLow;
    float CutLow;
    
    long flagCutHigh;
    float CutHigh;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} ctfEnvelopFunctionEstimateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ctfEnvelopFunctionEstimateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ctfEnvelopFunctionEstimateInfo* info);
extern void init1(ctfEnvelopFunctionEstimateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CTFENVELOPFUNCTIONESTIMATE_H */
