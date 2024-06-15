#ifndef MRCFETNORMALIZEBYSD_H
#define MRCFETNORMALIZEBYSD_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcFETnormalizeBySDInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInSample;
    char* InSample;
    FILE* fptInSample;
    
    long flagreadSD;
    char* readSD;
    FILE* fptreadSD;
    
    long flagwriteSD;
    char* writeSD;
    FILE* fptwriteSD;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcFETnormalizeBySDInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcFETnormalizeBySDInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcFETnormalizeBySDInfo* info);
extern void init1(mrcFETnormalizeBySDInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCFETNORMALIZEBYSD_H */
