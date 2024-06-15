#ifndef KHOROSFILTERGENERATE_H
#define KHOROSFILTERGENERATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct khorosFilterGenerateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagnx;
    long nx;
    
    long flagny;
    long ny;
    
    long flagw;
    float w;
    
    long flagh;
    float h;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} khorosFilterGenerateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(khorosFilterGenerateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(khorosFilterGenerateInfo* info);
extern void init1(khorosFilterGenerateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* KHOROSFILTERGENERATE_H */
