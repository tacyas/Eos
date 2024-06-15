#ifndef MRCIMAGEBANDPASSFILTER_H
#define MRCIMAGEBANDPASSFILTER_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageBandPassFilterInfo {
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
    
    long flaghvl;
    float hvl;
    
    long flaghvh;
    float hvh;
    
    long flagwl;
    float wl;
    
    long flagwh;
    float wh;
    
    long flaglowWeight;
    float lowWeight;
    
} mrcImageBandPassFilterInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageBandPassFilterInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageBandPassFilterInfo* info);
extern void init1(mrcImageBandPassFilterInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEBANDPASSFILTER_H */
