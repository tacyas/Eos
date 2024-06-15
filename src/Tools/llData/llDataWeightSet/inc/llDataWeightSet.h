#ifndef LLDATAWEIGHTSET_H
#define LLDATAWEIGHTSET_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataWeightSetInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagllInfo;
    char* llInfo;
    FILE* fptllInfo;
    
    long flagweight;
    float weight;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llDataWeightSetInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataWeightSetInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataWeightSetInfo* info);
extern void init1(llDataWeightSetInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATAWEIGHTSET_H */
