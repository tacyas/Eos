#ifndef MRCIMAGEADDVALUE_H
#define MRCIMAGEADDVALUE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageAddValueInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagValue;
    float Value;
    
    long flagcudaDeviceID;
    long cudaDeviceID;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageAddValueInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageAddValueInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageAddValueInfo* info);
extern void init1(mrcImageAddValueInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEADDVALUE_H */
