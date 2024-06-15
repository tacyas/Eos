#ifndef MRCIMAGESMOOTHING_H
#define MRCIMAGESMOOTHING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSmoothingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagsx;
    long sx;
    
    long flagsy;
    long sy;
    
    long flagsz;
    long sz;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSmoothingInfo;
extern void argCheck(mrcImageSmoothingInfo* info, int argc, char* avgv[]);
extern void init0(mrcImageSmoothingInfo* info);
extern void init1(mrcImageSmoothingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#endif /* MRCIMAGESMOOTHING_H */
