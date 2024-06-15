#ifndef MRCIMAGE3DWINDOWING_H
#define MRCIMAGE3DWINDOWING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImage3DWindowingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagcx;
    float cx;
    
    long flagcy;
    float cy;
    
    long flagcz;
    float cz;
    
    long flagwx;
    float wx;
    
    long flagwy;
    float wy;
    
    long flagwz;
    float wz;
    
    long flagr;
    float r;
    
    long flagw;
    float w;
    
    long flagwidthz;
    float widthz;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImage3DWindowingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImage3DWindowingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImage3DWindowingInfo* info);
extern void init1(mrcImage3DWindowingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGE3DWINDOWING_H */
