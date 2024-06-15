#ifndef MRCIMAGEESTIMATETILTIMAGE_H
#define MRCIMAGEESTIMATETILTIMAGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageEstimateTiltImageInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagTiltAngle;
    float TiltAngle;
    
    long flagTiltAxis;
    float TiltAxis;
    
    long Inverse;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageEstimateTiltImageInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageEstimateTiltImageInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageEstimateTiltImageInfo* info);
extern void init1(mrcImageEstimateTiltImageInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEESTIMATETILTIMAGE_H */
