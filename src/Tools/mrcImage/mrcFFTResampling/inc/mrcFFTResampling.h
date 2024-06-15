#ifndef MRCFFTRESAMPLING_H
#define MRCFFTRESAMPLING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcFFTResamplingInfo {
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
    
    long flagNx;
    float Nx;
    
    long flagNy;
    float Ny;
    
    long flagmode;
    long mode;
    
} mrcFFTResamplingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcFFTResamplingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcFFTResamplingInfo* info);
extern void init1(mrcFFTResamplingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCFFTRESAMPLING_H */
