#ifndef MRCIMAGECVE_H
#define MRCIMAGECVE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCVEInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagsx;
    long sx;
    
    long flagsy;
    long sy;
    
    long flagsz;
    long sz;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
} mrcImageCVEInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCVEInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCVEInfo* info);
extern void init1(mrcImageCVEInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECVE_H */