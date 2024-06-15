#ifndef MRCIMAGESYMMETRYAVERAGE_H
#define MRCIMAGESYMMETRYAVERAGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSymmetryAverageInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagNSym;
    float NSym;
    
    long flagcx;
    float cx;
    
    long flagcy;
    float cy;
    
    long flagcz;
    float cz;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSymmetryAverageInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSymmetryAverageInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSymmetryAverageInfo* info);
extern void init1(mrcImageSymmetryAverageInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESYMMETRYAVERAGE_H */
