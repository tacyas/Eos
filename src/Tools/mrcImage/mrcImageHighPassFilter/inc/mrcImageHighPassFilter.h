#ifndef MRCIMAGEHIGHPASSFILTER_H
#define MRCIMAGEHIGHPASSFILTER_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageHighPassFilterInfo {
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
    
    long flagmode;
    long mode;
    
    long flaghvp;
    float hvp;
    
    long flagpwLow;
    float pwLow;
    
    long flagpwHigh;
    float pwHigh;
    
    long flagwidth;
    float width;
    
} mrcImageHighPassFilterInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageHighPassFilterInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageHighPassFilterInfo* info);
extern void init1(mrcImageHighPassFilterInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEHIGHPASSFILTER_H */
