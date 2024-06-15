#ifndef MRCIMAGESUPERRESOLUTIONBYOPTICALFLOW_H
#define MRCIMAGESUPERRESOLUTIONBYOPTICALFLOW_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSuperResolutionByOpticalFlowInfo {
    long flagRedirect;

    long flagIn1;
    char* In1;
    FILE* fptIn1;
    
    long flagIn2;
    char* In2;
    FILE* fptIn2;
    
    long flagIn3;
    char* In3;
    FILE* fptIn3;
    
    long flagVx;
    char* Vx;
    FILE* fptVx;
    
    long flagVy;
    char* Vy;
    FILE* fptVy;
    
    long flagVz;
    char* Vz;
    FILE* fptVz;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagEnlarge;
    float Enlarge;
    
    long flagOutAVG;
    char* OutAVG;
    FILE* fptOutAVG;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSuperResolutionByOpticalFlowInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSuperResolutionByOpticalFlowInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSuperResolutionByOpticalFlowInfo* info);
extern void init1(mrcImageSuperResolutionByOpticalFlowInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESUPERRESOLUTIONBYOPTICALFLOW_H */
