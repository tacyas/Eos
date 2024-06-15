#ifndef MRCREFNOISEADD_H
#define MRCREFNOISEADD_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcRefNoiseAddInfo {
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
    
    long flagNoise;
    float Noise;
    
    long flagmode;
    long mode;
    
    long flagH;
    float H;
    
    long flagL;
    float L;
    
} mrcRefNoiseAddInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcRefNoiseAddInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcRefNoiseAddInfo* info);
extern void init1(mrcRefNoiseAddInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCREFNOISEADD_H */
