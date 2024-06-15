#ifndef MRCIMAGELOCALMAXIMUMVALUESFIND_H
#define MRCIMAGELOCALMAXIMUMVALUESFIND_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageLocalMaximumValuesFindInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutP;
    char* OutP;
    FILE* fptOutP;
    
    long flagThreshold;
    float Threshold;
    
    long flagSize;
    long Size;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageLocalMaximumValuesFindInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageLocalMaximumValuesFindInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageLocalMaximumValuesFindInfo* info);
extern void init1(mrcImageLocalMaximumValuesFindInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGELOCALMAXIMUMVALUESFIND_H */
