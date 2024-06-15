#ifndef MRCFFTLAYERLINECHECK_H
#define MRCFFTLAYERLINECHECK_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcFFTLayerLineCheckInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagL;
    long L;
    
    long NoEq;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcFFTLayerLineCheckInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcFFTLayerLineCheckInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcFFTLayerLineCheckInfo* info);
extern void init1(mrcFFTLayerLineCheckInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCFFTLAYERLINECHECK_H */
