#ifndef MRCIMAGEENHANCEMENTWITHFUZZYSETS_H
#define MRCIMAGEENHANCEMENTWITHFUZZYSETS_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageEnhancementWithFuzzySetsInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagFe;
    float Fe;
    
    long flagFd;
    float Fd;
    
    long flagr;
    long r;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageEnhancementWithFuzzySetsInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageEnhancementWithFuzzySetsInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageEnhancementWithFuzzySetsInfo* info);
extern void init1(mrcImageEnhancementWithFuzzySetsInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEENHANCEMENTWITHFUZZYSETS_H */
