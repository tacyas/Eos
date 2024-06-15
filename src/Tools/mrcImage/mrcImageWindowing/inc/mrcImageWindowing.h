#ifndef MRCIMAGEWINDOWING_H
#define MRCIMAGEWINDOWING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageWindowingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagWx;
    float Wx;
    
    long flagWxMax;
    float WxMax;
    
    long flagWy;
    float Wy;
    
    long flagWyMax;
    float WyMax;
    
    long flagWX;
    float WX;
    
    long flagWY;
    float WY;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageWindowingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageWindowingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageWindowingInfo* info);
extern void init1(mrcImageWindowingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEWINDOWING_H */
