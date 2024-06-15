#ifndef MRCIMAGESN_H
#define MRCIMAGESN_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSNInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagAvg;
    char* Avg;
    FILE* fptAvg;
    
    long flagTrimmedAvg;
    char* TrimmedAvg;
    FILE* fptTrimmedAvg;
    
    long flagMedian;
    char* Median;
    FILE* fptMedian;
    
    long flagSN;
    char* SN;
    FILE* fptSN;
    
    long flagt;
    char* t;
    FILE* fptt;
    
    long flagSE;
    char* SE;
    FILE* fptSE;
    
    long flagSD;
    char* SD;
    FILE* fptSD;
    
    long flagVar;
    char* Var;
    FILE* fptVar;
    
    long flagTrimmedRange;
    float TrimmedRange;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSNInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSNInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSNInfo* info);
extern void init1(mrcImageSNInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESN_H */
