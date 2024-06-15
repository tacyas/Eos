#ifndef MRCIMAGEGAUSSDISC_H
#define MRCIMAGEGAUSSDISC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageGaussDiscInfo {
    long flagRedirect;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagsigmax;
    float sigmax;
    
    long flagsigmay;
    float sigmay;
    
    long flagsigma_range;
    float sigma_range;
    
    long flagweight;
    float weight;
    
    long flagsize;
    float size;
    
    long flagWidth;
    float Width;
    
    long flagHeight;
    float Height;
    
    long flagcentrex;
    float centrex;
    
    long flagcentrey;
    float centrey;
    
    long flagAngle;
    float Angle;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageGaussDiscInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageGaussDiscInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageGaussDiscInfo* info);
extern void init1(mrcImageGaussDiscInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEGAUSSDISC_H */
