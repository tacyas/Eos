#ifndef LLDATAINFO_H
#define LLDATAINFO_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataInfoInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flaglayer;
    long layer;
    
    long flagNN;
    long NN;
    
    long flagLL;
    long LL;
    
    long flagmode;
    long mode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
} llDataInfoInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataInfoInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataInfoInfo* info);
extern void init1(llDataInfoInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATAINFO_H */
