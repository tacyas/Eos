#ifndef MRCIMAGECURL_H
#define MRCIMAGECURL_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCurlInfo {
    long flagRedirect;

    long flagIn2x;
    char* In2x;
    FILE* fptIn2x;
    
    long flagIn2y;
    char* In2y;
    FILE* fptIn2y;
    
    long flagIn3x;
    char* In3x;
    FILE* fptIn3x;
    
    long flagIn3y;
    char* In3y;
    FILE* fptIn3y;
    
    long flagIn3z;
    char* In3z;
    FILE* fptIn3z;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut3x;
    char* Out3x;
    FILE* fptOut3x;
    
    long flagOut3y;
    char* Out3y;
    FILE* fptOut3y;
    
    long flagOut3z;
    char* Out3z;
    FILE* fptOut3z;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageCurlInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCurlInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCurlInfo* info);
extern void init1(mrcImageCurlInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECURL_H */
