#ifndef MRCIMAGEREFCREATE_H
#define MRCIMAGEREFCREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageRefCreateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagiP;
    float iP;
    
    long flagiW;
    float iW;
    
    long flagiA;
    float iA;
    
    long flagWp;
    float Wp;
    
    long flagWw;
    float Ww;
    
    long flagWa;
    float Wa;
    
    long flagDp;
    float Dp;
    
    long flagDw;
    float Dw;
    
    long flagDa;
    float Da;
    
    long flagWx;
    long Wx;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageRefCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageRefCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageRefCreateInfo* info);
extern void init1(mrcImageRefCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEREFCREATE_H */
