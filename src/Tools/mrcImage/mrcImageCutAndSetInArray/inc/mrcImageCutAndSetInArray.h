#ifndef MRCIMAGECUTANDSETINARRAY_H
#define MRCIMAGECUTANDSETINARRAY_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCutAndSetInArrayInfo {
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
    
    long flagblank;
    long blank;
    
    long flagnumberOfParts;
    long numberOfParts;
    
    long flagmode;
    long mode;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
} mrcImageCutAndSetInArrayInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCutAndSetInArrayInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCutAndSetInArrayInfo* info);
extern void init1(mrcImageCutAndSetInArrayInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECUTANDSETINARRAY_H */
