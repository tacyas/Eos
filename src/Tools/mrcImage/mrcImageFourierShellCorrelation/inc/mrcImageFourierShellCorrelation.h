#ifndef MRCIMAGEFOURIERSHELLCORRELATION_H
#define MRCIMAGEFOURIERSHELLCORRELATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageFourierShellCorrelationInfo {
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
    
    long SNR;

    long FSCfull;

    long Cref;

    long flagBrestore;
    float Brestore;
    
    long flagdelta;
    float delta;
    
    long flagz;
    long z;
    
    long flagL;
    float L;
    
    long flagH;
    float H;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagmode2;
    long mode2;
    
    long flagIn1Array;
    char** In1Array;
    char* In1ArrayList;
    FILE** fptIn1Array;
    FILE* fptIn1ArrayList;
    
} mrcImageFourierShellCorrelationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageFourierShellCorrelationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageFourierShellCorrelationInfo* info);
extern void init1(mrcImageFourierShellCorrelationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEFOURIERSHELLCORRELATION_H */
