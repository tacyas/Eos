#ifndef MRCIMAGESCALARADD_H
#define MRCIMAGESCALARADD_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageScalarAddInfo {
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
    
    long flagx;
    float x;
    
    long flagy;
    float y;
    
    long flagz;
    float z;
    
    long flagValue;
    float Value;
    
    long flagmode;
    long mode;
    
} mrcImageScalarAddInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageScalarAddInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageScalarAddInfo* info);
extern void init1(mrcImageScalarAddInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESCALARADD_H */
