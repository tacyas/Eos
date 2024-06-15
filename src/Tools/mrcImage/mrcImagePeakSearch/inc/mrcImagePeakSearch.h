#ifndef MRCIMAGEPEAKSEARCH_H
#define MRCIMAGEPEAKSEARCH_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImagePeakSearchInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutB;
    char* OutB;
    FILE* fptOutB;
    
    long flagOutL;
    char* OutL;
    FILE* fptOutL;
    
    long flagOutA;
    char* OutA;
    FILE* fptOutA;
    
    long flagOutStatics;
    char* OutStatics;
    FILE* fptOutStatics;
    
    long flagSigma;
    float Sigma;
    
    long flagThreshold;
    float Threshold;
    
    long flagArea;
    float Area;
    
    long flagAreaPixel;
    float AreaPixel;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImagePeakSearchInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImagePeakSearchInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImagePeakSearchInfo* info);
extern void init1(mrcImagePeakSearchInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEPEAKSEARCH_H */
