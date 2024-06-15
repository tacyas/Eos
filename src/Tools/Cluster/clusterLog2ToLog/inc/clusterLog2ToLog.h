#ifndef CLUSTERLOG2TOLOG_H
#define CLUSTERLOG2TOLOG_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct clusterLog2ToLogInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flaglastNum;
    long lastNum;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} clusterLog2ToLogInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(clusterLog2ToLogInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(clusterLog2ToLogInfo* info);
extern void init1(clusterLog2ToLogInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CLUSTERLOG2TOLOG_H */
