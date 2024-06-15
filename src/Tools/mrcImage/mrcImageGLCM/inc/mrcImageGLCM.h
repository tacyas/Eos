#ifndef MRCIMAGEGLCM_H
#define MRCIMAGEGLCM_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageGLCMInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutInfo;
    char* OutInfo;
    FILE* fptOutInfo;
    
    long flagepsilon;
    float epsilon;
    
    long flagthresHigh;
    float thresHigh;
    
    long flagthresLow;
    float thresLow;
    
    long flagexceptValue;
    float exceptValue;
    
    long flagrange;
    float range;
    
    long flagnHist;
    long nHist;
    
    long flagoffset;
    long offset;
    
    long flagangleMode;
    long angleMode;
    
    long flagminAreaX;
    float minAreaX;
    
    long flagmaxAreaX;
    float maxAreaX;
    
    long flagminAreaY;
    float minAreaY;
    
    long flagmaxAreaY;
    float maxAreaY;
    
    long flagminAreaZ;
    float minAreaZ;
    
    long flagmaxAreaZ;
    float maxAreaZ;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageGLCMInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageGLCMInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageGLCMInfo* info);
extern void init1(mrcImageGLCMInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEGLCM_H */
