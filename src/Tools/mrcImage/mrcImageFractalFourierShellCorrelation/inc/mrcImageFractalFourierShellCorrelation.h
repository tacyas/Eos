#ifndef MRCIMAGEFRACTALFOURIERSHELLCORRELATION_H
#define MRCIMAGEFRACTALFOURIERSHELLCORRELATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageFractalFourierShellCorrelationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagThreshold;
    float Threshold;
    
    long flagstepx;
    float stepx;
    
    long flagstepy;
    float stepy;
    
    long flagstepz;
    float stepz;
    
    long flagmaxN;
    float maxN;
    
    long flagscaling;
    float scaling;
    
    long flaggetMode;
    long getMode;
    
    long flagLog;
    char* Log;
    FILE* fptLog;
    
    long flagxmin;
    float xmin;
    
    long flagymin;
    float ymin;
    
    long flagzmin;
    float zmin;
    
    long flagxmax;
    float xmax;
    
    long flagymax;
    float ymax;
    
    long flagzmax;
    float zmax;
    
    long flagdensityThreshold;
    float densityThreshold;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageFractalFourierShellCorrelationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageFractalFourierShellCorrelationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageFractalFourierShellCorrelationInfo* info);
extern void init1(mrcImageFractalFourierShellCorrelationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEFRACTALFOURIERSHELLCORRELATION_H */
