#ifndef MRCREFIMAGEPWZCORRELATION_H
#define MRCREFIMAGEPWZCORRELATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcRefImagepwzCorrelationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagdy;
    long dy;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagmode2;
    long mode2;
    
} mrcRefImagepwzCorrelationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcRefImagepwzCorrelationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcRefImagepwzCorrelationInfo* info);
extern void init1(mrcRefImagepwzCorrelationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCREFIMAGEPWZCORRELATION_H */
