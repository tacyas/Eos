#ifndef MRCIMAGECLUSTERANALYSISPVM_H
#define MRCIMAGECLUSTERANALYSISPVM_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageClusterAnalysisPVMInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long Output;

    long flagN;
    long N;
    
    long Iteration;

    long flagAutoRotation;
    long AutoRotation;
    
    long flagAutoRotationIteration;
    long AutoRotationIteration;
    
    long flagAutoRotationMethod;
    long AutoRotationMethod;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long Mirrorimage;

    long flagcorrelationMode;
    long correlationMode;
    
    long flagMaxprocess;
    long Maxprocess;
    
    long flagmode;
    long mode;
    
} mrcImageClusterAnalysisPVMInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageClusterAnalysisPVMInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageClusterAnalysisPVMInfo* info);
extern void init1(mrcImageClusterAnalysisPVMInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECLUSTERANALYSISPVM_H */
