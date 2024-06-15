#ifndef MRCIMAGENORMALIZEDSUBTRACTION_H
#define MRCIMAGENORMALIZEDSUBTRACTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageNormalizedSubtractionInfo {
    long flagRedirect;

    long flagIn1;
    char* In1;
    FILE* fptIn1;
    
    long flagIn2;
    char* In2;
    FILE* fptIn2;
    
    long flagIn2_tmp;
    char* In2_tmp;
    FILE* fptIn2_tmp;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRMSD;
    char* RMSD;
    FILE* fptRMSD;
    
    long flagParamFile;
    char* ParamFile;
    FILE* fptParamFile;
    
    long flagmode;
    long mode;
    
} mrcImageNormalizedSubtractionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageNormalizedSubtractionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageNormalizedSubtractionInfo* info);
extern void init1(mrcImageNormalizedSubtractionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGENORMALIZEDSUBTRACTION_H */
