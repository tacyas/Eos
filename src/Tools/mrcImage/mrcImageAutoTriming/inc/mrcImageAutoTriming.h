#ifndef MRCIMAGEAUTOTRIMING_H
#define MRCIMAGEAUTOTRIMING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageAutoTrimingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutParam;
    char* OutParam;
    FILE* fptOutParam;
    
    long flagEAMode;
    char* EAMode;
    
    long flagRot1Min;
    float Rot1Min;
    
    long flagRot1Max;
    float Rot1Max;
    
    long flagRot1Delta;
    float Rot1Delta;
    
    long flagRot2Min;
    float Rot2Min;
    
    long flagRot2Max;
    float Rot2Max;
    
    long flagRot2Delta;
    float Rot2Delta;
    
    long flagRot3Min;
    float Rot3Min;
    
    long flagRot3Max;
    float Rot3Max;
    
    long flagRot3Delta;
    float Rot3Delta;
    
    long flagInterpolationMode;
    long InterpolationMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageAutoTrimingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageAutoTrimingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageAutoTrimingInfo* info);
extern void init1(mrcImageAutoTrimingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEAUTOTRIMING_H */
