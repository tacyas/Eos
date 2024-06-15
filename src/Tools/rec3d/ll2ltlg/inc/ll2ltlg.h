#ifndef LL2LTLG_H
#define LL2LTLG_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ll2ltlgInfo {
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
    
    long flagTitle;
    char* Title;
    
    long flagllMax;
    long llMax;
    
    long flagdelRInv;
    float delRInv;
    
    long flagRMaxInv;
    float RMaxInv;
    
    long flagdelr;
    float delr;
    
    long flagrMax;
    float rMax;
    
    long flagflagOutputInfo;
    long flagOutputInfo;
    
    long flagmode;
    long mode;
    
} ll2ltlgInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ll2ltlgInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ll2ltlgInfo* info);
extern void init1(ll2ltlgInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LL2LTLG_H */
