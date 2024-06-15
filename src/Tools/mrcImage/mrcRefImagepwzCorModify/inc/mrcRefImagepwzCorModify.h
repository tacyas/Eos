#ifndef MRCREFIMAGEPWZCORMODIFY_H
#define MRCREFIMAGEPWZCORMODIFY_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcRefImagepwzCorModifyInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagNry;
    long Nry;
    
    long flagmag;
    float mag;
    
    long flagshift;
    float shift;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagmode2;
    long mode2;
    
} mrcRefImagepwzCorModifyInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcRefImagepwzCorModifyInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcRefImagepwzCorModifyInfo* info);
extern void init1(mrcRefImagepwzCorModifyInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCREFIMAGEPWZCORMODIFY_H */
