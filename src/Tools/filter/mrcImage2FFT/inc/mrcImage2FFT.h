#ifndef MRCIMAGE2FFT_H
#define MRCIMAGE2FFT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImage2FFTInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagCentreX;
    float CentreX;
    
    long flagCentreY;
    float CentreY;
    
    long flagCentreZ;
    float CentreZ;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImage2FFTInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImage2FFTInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImage2FFTInfo* info);
extern void init1(mrcImage2FFTInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGE2FFT_H */
