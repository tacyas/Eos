#ifndef MRCREFIMAGEXAFIT_H
#define MRCREFIMAGEXAFIT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcRefImagexaFitInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagix;
    long ix;
    
    long flagia;
    float ia;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagDy;
    long Dy;
    
    long flagxrange;
    long xrange;
    
    long flagarange;
    long arange;
    
    long flagValue;
    float Value;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagmode2;
    long mode2;
    
} mrcRefImagexaFitInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcRefImagexaFitInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcRefImagexaFitInfo* info);
extern void init1(mrcRefImagexaFitInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCREFIMAGEXAFIT_H */
