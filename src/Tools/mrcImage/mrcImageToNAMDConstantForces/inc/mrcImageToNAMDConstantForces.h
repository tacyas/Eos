#ifndef MRCIMAGETONAMDCONSTANTFORCES_H
#define MRCIMAGETONAMDCONSTANTFORCES_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageToNAMDConstantForcesInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInPDB;
    char* InPDB;
    FILE* fptInPDB;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagWeight;
    float Weight;
    
    long flagScalingFactor;
    float ScalingFactor;
    
    long flagContour;
    float Contour;
    
    long flagRotate;
    long Rotate;
    
    long flagRWeight;
    float RWeight;
    
    long flagSeed;
    float Seed;
    
    long nowater;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageToNAMDConstantForcesInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageToNAMDConstantForcesInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageToNAMDConstantForcesInfo* info);
extern void init1(mrcImageToNAMDConstantForcesInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGETONAMDCONSTANTFORCES_H */
