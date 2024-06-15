#ifndef MRCIMAGENULLIMAGECREATE_H
#define MRCIMAGENULLIMAGECREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageNullImageCreateInfo {
    long flagRedirect;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagNz;
    long Nz;
    
    long flagValue;
    float Value;
    
    long flagd;
    float d;
    
    long flagMode;
    long Mode;
    
    long Default;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageNullImageCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageNullImageCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageNullImageCreateInfo* info);
extern void init1(mrcImageNullImageCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGENULLIMAGECREATE_H */
