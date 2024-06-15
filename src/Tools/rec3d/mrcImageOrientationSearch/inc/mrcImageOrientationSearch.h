#ifndef MRCIMAGEORIENTATIONSEARCH_H
#define MRCIMAGEORIENTATIONSEARCH_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageOrientationSearchInfo {
    long flagRedirect;

    long flagIn1;
    char** In1;
    char* In1List;
    FILE** fptIn1;
    FILE* fptIn1List;
    
    long flagIn2;
    char** In2;
    char* In2List;
    FILE** fptIn2;
    FILE* fptIn2List;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagthreshold;
    float threshold;
    
} mrcImageOrientationSearchInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageOrientationSearchInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageOrientationSearchInfo* info);
extern void init1(mrcImageOrientationSearchInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEORIENTATIONSEARCH_H */
