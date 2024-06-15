#ifndef RANDOMUNIFORMGET_H
#define RANDOMUNIFORMGET_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct randomUniformGetInfo {
    long flagRedirect;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagmin;
    float min;
    
    long flagmax;
    float max;
    
    long flagnum;
    long num;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} randomUniformGetInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(randomUniformGetInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(randomUniformGetInfo* info);
extern void init1(randomUniformGetInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* RANDOMUNIFORMGET_H */
