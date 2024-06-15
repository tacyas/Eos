#ifndef MRCIMAGELOGICALOPERATION_H
#define MRCIMAGELOGICALOPERATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageLogicalOperationInfo {
    long flagRedirect;

    long flagIn1;
    char* In1;
    FILE* fptIn1;
    
    long flagIn2;
    char* In2;
    FILE* fptIn2;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageLogicalOperationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageLogicalOperationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageLogicalOperationInfo* info);
extern void init1(mrcImageLogicalOperationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGELOGICALOPERATION_H */
