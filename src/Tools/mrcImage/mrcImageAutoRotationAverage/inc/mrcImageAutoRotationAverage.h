#ifndef MRCIMAGEAUTOROTATIONAVERAGE_H
#define MRCIMAGEAUTOROTATIONAVERAGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageAutoRotationAverageInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagMin;
    float Min;
    
    long flagMax;
    float Max;
    
    long flagDelta;
    float Delta;
    
    long flagIter;
    long Iter;
    
    long flagiter;
    long iter;
    
    long flagCorMode;
    long CorMode;
    
    long flagMethod;
    long Method;
    
    long Periodic;

    long flagmaxIter;
    long maxIter;
    
    long flagrmsd;
    float rmsd;
    
    long flagLog;
    char* Log;
    FILE* fptLog;
    
    long flagThres;
    float Thres;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageAutoRotationAverageInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageAutoRotationAverageInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageAutoRotationAverageInfo* info);
extern void init1(mrcImageAutoRotationAverageInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEAUTOROTATIONAVERAGE_H */
