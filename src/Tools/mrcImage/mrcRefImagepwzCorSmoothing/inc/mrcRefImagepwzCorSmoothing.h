#ifndef MRCREFIMAGEPWZCORSMOOTHING_H
#define MRCREFIMAGEPWZCORSMOOTHING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcRefImagepwzCorSmoothingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagN;
    long N;
    
    long flagdp;
    float dp;
    
    long flagdz;
    float dz;
    
    long flagmode;
    long mode;
    
} mrcRefImagepwzCorSmoothingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcRefImagepwzCorSmoothingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcRefImagepwzCorSmoothingInfo* info);
extern void init1(mrcRefImagepwzCorSmoothingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCREFIMAGEPWZCORSMOOTHING_H */
