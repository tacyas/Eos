#ifndef CHECKORIENTATIONBYDEGREE_H
#define CHECKORIENTATIONBYDEGREE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct CheckOrientationByDegreeInfo {
    long flagRedirect;

    long flagInbase;
    char* Inbase;
    FILE* fptInbase;
    
    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagmodechanging;
    long modechanging;
    
} CheckOrientationByDegreeInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(CheckOrientationByDegreeInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(CheckOrientationByDegreeInfo* info);
extern void init1(CheckOrientationByDegreeInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CHECKORIENTATIONBYDEGREE_H */
