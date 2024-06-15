#ifndef MRCFFTDIGITIZE_H
#define MRCFFTDIGITIZE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcFFTDigitizeInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagLevel;
    float Level;
    
    long flagMin;
    float Min;
    
    long flagMax;
    float Max;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcFFTDigitizeInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcFFTDigitizeInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcFFTDigitizeInfo* info);
extern void init1(mrcFFTDigitizeInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCFFTDIGITIZE_H */
