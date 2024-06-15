#ifndef MRCIMAGEMASKINGBYIMAGE_H
#define MRCIMAGEMASKINGBYIMAGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageMaskingByImageInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagMaskFile;
    char* MaskFile;
    FILE* fptMaskFile;
    
    long flagCutValue;
    float CutValue;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageMaskingByImageInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageMaskingByImageInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageMaskingByImageInfo* info);
extern void init1(mrcImageMaskingByImageInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMASKINGBYIMAGE_H */
