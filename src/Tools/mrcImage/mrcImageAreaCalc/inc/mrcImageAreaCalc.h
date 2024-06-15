#ifndef MRCIMAGEAREACALC_H
#define MRCIMAGEAREACALC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageAreaCalcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutInfo;
    char* OutInfo;
    FILE* fptOutInfo;
    
    long flagLabel;
    char* Label;
    FILE* fptLabel;
    
    long flagOutHist;
    char* OutHist;
    FILE* fptOutHist;
    
    long flagDelHist;
    float DelHist;
    
    long flagNeighbor;
    float Neighbor;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageAreaCalcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageAreaCalcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageAreaCalcInfo* info);
extern void init1(mrcImageAreaCalcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEAREACALC_H */
