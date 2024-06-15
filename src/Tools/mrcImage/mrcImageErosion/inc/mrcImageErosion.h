#ifndef MRCIMAGEEROSION_H
#define MRCIMAGEEROSION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageErosionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutSE;
    char* OutSE;
    FILE* fptOutSE;
    
    long flagSEmode;
    long SEmode;
    
    long flagradius;
    long radius;
    
    long flagn;
    long n;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageErosionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageErosionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageErosionInfo* info);
extern void init1(mrcImageErosionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEEROSION_H */
