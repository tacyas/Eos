#ifndef MRCIMAGETOPHATTRANSFORM_H
#define MRCIMAGETOPHATTRANSFORM_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageTopHatTransformInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagtimes;
    long times;
    
    long flagOutSE;
    char* OutSE;
    FILE* fptOutSE;
    
    long flagSEmode;
    long SEmode;
    
    long flagradius;
    long radius;
    
    long flagn;
    long n;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageTopHatTransformInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageTopHatTransformInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageTopHatTransformInfo* info);
extern void init1(mrcImageTopHatTransformInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGETOPHATTRANSFORM_H */
