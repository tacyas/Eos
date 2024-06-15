#ifndef FETSMALLMAPSETCREATE_FORSIMULTANEOUSMINIMIZATION_H
#define FETSMALLMAPSETCREATE_FORSIMULTANEOUSMINIMIZATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct FETsmallMapSetCreate_forSimultaneousMinimizationInfo {
    long flagRedirect;

    long flagInML;
    char* InML;
    FILE* fptInML;
    
    long flagOutMS;
    char* OutMS;
    FILE* fptOutMS;
    
    long flagInSS;
    long InSS;
    
    long flagInSR;
    long InSR;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} FETsmallMapSetCreate_forSimultaneousMinimizationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(FETsmallMapSetCreate_forSimultaneousMinimizationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(FETsmallMapSetCreate_forSimultaneousMinimizationInfo* info);
extern void init1(FETsmallMapSetCreate_forSimultaneousMinimizationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* FETSMALLMAPSETCREATE_FORSIMULTANEOUSMINIMIZATION_H */
