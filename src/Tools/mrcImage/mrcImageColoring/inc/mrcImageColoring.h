#ifndef MRCIMAGECOLORING_H
#define MRCIMAGECOLORING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageColoringInfo {
    long flagRedirect;

    long flagrIn;
    char* rIn;
    FILE* fptrIn;
    
    long flaggIn;
    char* gIn;
    FILE* fptgIn;
    
    long flagbIn;
    char* bIn;
    FILE* fptbIn;
    
    long flagrHigh;
    float rHigh;
    
    long flagrLow;
    float rLow;
    
    long flaggHigh;
    float gHigh;
    
    long flaggLow;
    float gLow;
    
    long flagbHigh;
    float bHigh;
    
    long flagbLow;
    float bLow;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageColoringInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageColoringInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageColoringInfo* info);
extern void init1(mrcImageColoringInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECOLORING_H */
