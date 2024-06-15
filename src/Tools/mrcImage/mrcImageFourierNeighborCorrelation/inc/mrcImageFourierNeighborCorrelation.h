#ifndef MRCIMAGEFOURIERNEIGHBORCORRELATION_H
#define MRCIMAGEFOURIERNEIGHBORCORRELATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageFourierNeighborCorrelationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagdelta;
    float delta;
    
    long flagCentre;
    long Centre;
    
    long flagGetMode;
    long GetMode;
    
    long FSC;

    long Cref;

    long FSCfull;

    long flagBrestore;
    float Brestore;
    
    long flagInMask;
    char* InMask;
    FILE* fptInMask;
    
    long flagInBackMask;
    char* InBackMask;
    FILE* fptInBackMask;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageFourierNeighborCorrelationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageFourierNeighborCorrelationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageFourierNeighborCorrelationInfo* info);
extern void init1(mrcImageFourierNeighborCorrelationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEFOURIERNEIGHBORCORRELATION_H */
