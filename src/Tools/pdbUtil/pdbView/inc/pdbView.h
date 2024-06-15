#ifndef PDBVIEW_H
#define PDBVIEW_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbViewInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInDCD;
    char* InDCD;
    FILE* fptInDCD;
    
    long flagStep;
    long Step;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagDisplayMode;
    long DisplayMode;
    
    long flagAtomMode;
    long AtomMode;
    
    long flagColorMode;
    long ColorMode;
    
    long flagmode;
    long mode;
    
} pdbViewInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbViewInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbViewInfo* info);
extern void init1(pdbViewInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBVIEW_H */
