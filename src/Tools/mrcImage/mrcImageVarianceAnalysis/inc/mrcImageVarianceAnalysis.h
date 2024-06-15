#ifndef MRCIMAGEVARIANCEANALYSIS_H
#define MRCIMAGEVARIANCEANALYSIS_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageVarianceAnalysisInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutV;
    char* OutV;
    FILE* fptOutV;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageVarianceAnalysisInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageVarianceAnalysisInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageVarianceAnalysisInfo* info);
extern void init1(mrcImageVarianceAnalysisInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEVARIANCEANALYSIS_H */
