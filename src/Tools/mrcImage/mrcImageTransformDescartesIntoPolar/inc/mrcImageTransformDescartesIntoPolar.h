#ifndef MRCIMAGETRANSFORMDESCARTESINTOPOLAR_H
#define MRCIMAGETRANSFORMDESCARTESINTOPOLAR_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageTransformDescartesIntoPolarInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagdr;
    float dr;
    
    long flagdtheta;
    float dtheta;
    
    long flagdphi;
    float dphi;
    
    long flagzx;
    float zx;
    
    long flagzy;
    float zy;
    
    long flagzz;
    float zz;
    
    long flagxx;
    float xx;
    
    long flagxy;
    float xy;
    
    long flagxz;
    float xz;
    
    long flagcx;
    float cx;
    
    long flagcy;
    float cy;
    
    long flagcz;
    float cz;
    
    long rweight;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageTransformDescartesIntoPolarInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageTransformDescartesIntoPolarInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageTransformDescartesIntoPolarInfo* info);
extern void init1(mrcImageTransformDescartesIntoPolarInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGETRANSFORMDESCARTESINTOPOLAR_H */
