#ifndef POINTAFFINETRANSFORM_H
#define POINTAFFINETRANSFORM_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pointAffineTransformInfo {
    long flagRedirect;

    long flagX;
    float X;
    
    long flagY;
    float Y;
    
    long flagZ;
    float Z;
    
    long flagEuler;
    char* Euler;
    
    long flagRot1;
    float Rot1;
    
    long flagRot2;
    float Rot2;
    
    long flagRot3;
    float Rot3;
    
    long flagdX;
    float dX;
    
    long flagdY;
    float dY;
    
    long flagdZ;
    float dZ;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pointAffineTransformInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pointAffineTransformInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pointAffineTransformInfo* info);
extern void init1(pointAffineTransformInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* POINTAFFINETRANSFORM_H */
