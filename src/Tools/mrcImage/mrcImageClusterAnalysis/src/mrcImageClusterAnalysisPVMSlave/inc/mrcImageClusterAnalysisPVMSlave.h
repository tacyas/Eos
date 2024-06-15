#ifndef MRCIMAGECLUSTERANALYSISPVMSLAVE_H
#define MRCIMAGECLUSTERANALYSISPVMSLAVE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageClusterAnalysisPVMSlaveInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageClusterAnalysisPVMSlaveInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageClusterAnalysisPVMSlaveInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageClusterAnalysisPVMSlaveInfo* info);
extern void init1(mrcImageClusterAnalysisPVMSlaveInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECLUSTERANALYSISPVMSLAVE_H */
