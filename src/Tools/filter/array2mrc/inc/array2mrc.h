#ifndef ARRAY2MRC_H
#define ARRAY2MRC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct array2mrcInfo {
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
    
    long flagax;
    long ax;
    
    long flagay;
    long ay;
    
    long flagaz;
    long az;
    
    long flagmode;
    long mode;
    
    long flagmm;
    long mm;
    
    long flaglm;
    float lm;
    
    long flaglmx;
    float lmx;
    
    long flaglmy;
    float lmy;
    
    long flaglmz;
    float lmz;
    
} array2mrcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(array2mrcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(array2mrcInfo* info);
extern void init1(array2mrcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* ARRAY2MRC_H */
