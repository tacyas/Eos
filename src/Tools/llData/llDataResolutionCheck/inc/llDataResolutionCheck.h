#ifndef LLDATARESOLUTIONCHECK_H
#define LLDATARESOLUTIONCHECK_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataResolutionCheckInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llDataResolutionCheckInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataResolutionCheckInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataResolutionCheckInfo* info);
extern void init1(llDataResolutionCheckInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATARESOLUTIONCHECK_H */
