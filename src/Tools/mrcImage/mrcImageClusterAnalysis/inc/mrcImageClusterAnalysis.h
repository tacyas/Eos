#ifndef MRCIMAGECLUSTERANALYSIS_H
#define MRCIMAGECLUSTERANALYSIS_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageClusterAnalysisInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long Output;

    long flagN;
    long N;
    
    long flagMin;
    float Min;
    
    long Iteration;

    long flagAutoRotation;
    long AutoRotation;
    
    long flagARMin;
    float ARMin;
    
    long flagARMax;
    float ARMax;
    
    long flagAutoRotationIteration;
    long AutoRotationIteration;
    
    long flagAutoRotationMethod;
    long AutoRotationMethod;
    
    long flagcorrelationMode;
    long correlationMode;
    
    long flagLog;
    char* Log;
    FILE* fptLog;
    
    long flagLog2;
    char* Log2;
    FILE* fptLog2;
    
    long flagLogIn;
    char* LogIn;
    FILE* fptLogIn;
    
    long flagprevFileNum;
    long prevFileNum;
    
    long flagpthread;
    long pthread;
    
    long NoRecalc;

    long pvm;

    long flagpvmList;
    char* pvmList;
    FILE* fptpvmList;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageClusterAnalysisInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageClusterAnalysisInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageClusterAnalysisInfo* info);
extern void init1(mrcImageClusterAnalysisInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECLUSTERANALYSIS_H */
