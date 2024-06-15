#ifndef DCDINFO_H
#define DCDINFO_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct dcdInfoInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInPDB;
    char* InPDB;
    FILE* fptInPDB;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutPDB;
    char* OutPDB;
    FILE* fptOutPDB;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} dcdInfoInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(dcdInfoInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(dcdInfoInfo* info);
extern void init1(dcdInfoInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* DCDINFO_H */
