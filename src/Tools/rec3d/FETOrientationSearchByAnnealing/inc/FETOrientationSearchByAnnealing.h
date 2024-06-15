#ifndef FETORIENTATIONSEARCHBYANNEALING_H
#define FETORIENTATIONSEARCHBYANNEALING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct FETOrientationSearchByAnnealingInfo {
    long flagRedirect;

    long flagInMS;
    char* InMS;
    FILE* fptInMS;
    
    long flagInFL;
    char* InFL;
    FILE* fptInFL;
    
    long flagInML;
    char* InML;
    FILE* fptInML;
    
    long flagITemp;
    float ITemp;
    
    long flagAS1;
    long AS1;
    
    long flagAS2;
    float AS2;
    
    long flagAS3;
    long AS3;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} FETOrientationSearchByAnnealingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(FETOrientationSearchByAnnealingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(FETOrientationSearchByAnnealingInfo* info);
extern void init1(FETOrientationSearchByAnnealingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* FETORIENTATIONSEARCHBYANNEALING_H */
