#ifndef MRCREFIMAGEPWZCORPEAKFIND_H
#define MRCREFIMAGEPWZCORPEAKFIND_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcRefImagepwzCorPeakFindInfo {
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
    
    long flagN;
    long N;
    
    long flagdN;
    long dN;
    
    long flagdp;
    float dp;
    
    long flagdz;
    float dz;
    
    long flaglength;
    long length;
    
    long flagdiv;
    long div;
    
    long flagmode;
    long mode;
    
    long flagmode2;
    long mode2;
    
} mrcRefImagepwzCorPeakFindInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcRefImagepwzCorPeakFindInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcRefImagepwzCorPeakFindInfo* info);
extern void init1(mrcRefImagepwzCorPeakFindInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCREFIMAGEPWZCORPEAKFIND_H */
