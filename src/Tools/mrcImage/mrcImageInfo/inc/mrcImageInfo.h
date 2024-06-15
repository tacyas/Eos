#ifndef MRCIMAGEINFO_H
#define MRCIMAGEINFO_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageInfoInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagX;
    float X;
    
    long flagY;
    float Y;
    
    long xProjection;

    long yProjection;

    long Length;

    long flagH;
    long H;
    
    long flagH2;
    float H2;
    
    long flagH3;
    long H3;
    
    long flagH4;
    float H4;
    
    long flagH5;
    long H5;
    
    long flagH6;
    float H6;
    
    long flagLow;
    float Low;
    
    long flagHigh;
    float High;
    
    long flagThres;
    float Thres;
    
    long Info;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagrmax;
    float rmax;
    
    long flagmode;
    long mode;
    
} mrcImageInfoInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageInfoInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageInfoInfo* info);
extern void init1(mrcImageInfoInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEINFO_H */
