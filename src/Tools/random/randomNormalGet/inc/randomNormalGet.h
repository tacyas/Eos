#ifndef RANDOMNORMALGET_H
#define RANDOMNORMALGET_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct randomNormalGetInfo {
    long flagRedirect;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutMRC;
    char* OutMRC;
    FILE* fptOutMRC;
    
    long flagN;
    long N;
    
    long flagAve;
    float Ave;
    
    long flagSD;
    float SD;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} randomNormalGetInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(randomNormalGetInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(randomNormalGetInfo* info);
extern void init1(randomNormalGetInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* RANDOMNORMALGET_H */
