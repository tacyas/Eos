#ifndef MRCIMAGEADAPTIVEBINALIZATION_H
#define MRCIMAGEADAPTIVEBINALIZATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageAdaptiveBinalizationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagSize;
    long Size;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageAdaptiveBinalizationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageAdaptiveBinalizationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageAdaptiveBinalizationInfo* info);
extern void init1(mrcImageAdaptiveBinalizationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEADAPTIVEBINALIZATION_H */
