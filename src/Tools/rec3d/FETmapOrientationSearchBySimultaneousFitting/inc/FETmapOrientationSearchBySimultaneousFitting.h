#ifndef FETMAPORIENTATIONSEARCHBYSIMULTANEOUSFITTING_H
#define FETMAPORIENTATIONSEARCHBYSIMULTANEOUSFITTING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct FETmapOrientationSearchBySimultaneousFittingInfo {
    long flagRedirect;

    long flagInML;
    char* InML;
    FILE* fptInML;
    
    long flagInNL;
    char* InNL;
    FILE* fptInNL;
    
    long flagInCL;
    char* InCL;
    FILE* fptInCL;
    
    long flagPM;
    long PM;
    
    long flagPN;
    long PN;
    
    long flagPDT;
    float PDT;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} FETmapOrientationSearchBySimultaneousFittingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(FETmapOrientationSearchBySimultaneousFittingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(FETmapOrientationSearchBySimultaneousFittingInfo* info);
extern void init1(FETmapOrientationSearchBySimultaneousFittingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* FETMAPORIENTATIONSEARCHBYSIMULTANEOUSFITTING_H */
