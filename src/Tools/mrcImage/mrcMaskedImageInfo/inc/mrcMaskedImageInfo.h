#ifndef MRCMASKEDIMAGEINFO_H
#define MRCMASKEDIMAGEINFO_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcMaskedImageInfoInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagMaskedValue;
    float MaskedValue;
    
    long flagEpsilon;
    float Epsilon;
    
    long flagnQuantile;
    long nQuantile;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcMaskedImageInfoInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcMaskedImageInfoInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcMaskedImageInfoInfo* info);
extern void init1(mrcMaskedImageInfoInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCMASKEDIMAGEINFO_H */
