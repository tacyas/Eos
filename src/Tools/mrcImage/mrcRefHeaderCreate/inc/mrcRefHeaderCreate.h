#ifndef MRCREFHEADERCREATE_H
#define MRCREFHEADERCREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcRefHeaderCreateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
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
    
    long flagSy;
    long Sy;
    
    long flagEy;
    long Ey;
    
    long flagRefsize;
    long Refsize;
    
    long flagmode;
    long mode;
    
} mrcRefHeaderCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcRefHeaderCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcRefHeaderCreateInfo* info);
extern void init1(mrcRefHeaderCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCREFHEADERCREATE_H */
