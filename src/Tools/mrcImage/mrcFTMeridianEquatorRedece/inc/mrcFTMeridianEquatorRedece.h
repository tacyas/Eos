#ifndef MRCFTMERIDIANEQUATORREDECE_H
#define MRCFTMERIDIANEQUATORREDECE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcFTMeridianEquatorRedeceInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutFFT;
    char* OutFFT;
    FILE* fptOutFFT;
    
    long flagMaxX;
    long MaxX;
    
    long flagMaxY;
    long MaxY;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcFTMeridianEquatorRedeceInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcFTMeridianEquatorRedeceInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcFTMeridianEquatorRedeceInfo* info);
extern void init1(mrcFTMeridianEquatorRedeceInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCFTMERIDIANEQUATORREDECE_H */
