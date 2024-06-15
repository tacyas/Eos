#ifndef MRCFFTFILTERING_H
#define MRCFFTFILTERING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcFFTFilteringInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagIQ;
    char* IQ;
    FILE* fptIQ;
    
    long flagvx;
    float vx;
    
    long flagvy;
    float vy;
    
    long flagv1x;
    float v1x;
    
    long flagv1y;
    float v1y;
    
    long flagv2x;
    float v2x;
    
    long flagv2y;
    float v2y;
    
    long flagsx;
    long sx;
    
    long flagsy;
    long sy;
    
    long neglectF00;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcFFTFilteringInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcFFTFilteringInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcFFTFilteringInfo* info);
extern void init1(mrcFFTFilteringInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCFFTFILTERING_H */
