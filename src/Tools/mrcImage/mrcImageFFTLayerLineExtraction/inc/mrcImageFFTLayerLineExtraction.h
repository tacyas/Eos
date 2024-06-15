#ifndef MRCIMAGEFFTLAYERLINEEXTRACTION_H
#define MRCIMAGEFFTLAYERLINEEXTRACTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageFFTLayerLineExtractionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInI;
    char* InI;
    FILE* fptInI;
    
    long flagtruePitch;
    float truePitch;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageFFTLayerLineExtractionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageFFTLayerLineExtractionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageFFTLayerLineExtractionInfo* info);
extern void init1(mrcImageFFTLayerLineExtractionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEFFTLAYERLINEEXTRACTION_H */
