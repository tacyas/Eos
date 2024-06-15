#ifndef MRCIMAGERADIALDISTRIBUTION_H
#define MRCIMAGERADIALDISTRIBUTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageRadialDistributionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut2;
    char* Out2;
    FILE* fptOut2;
    
    long flagCx;
    float Cx;
    
    long flagCy;
    float Cy;
    
    long flagCsx;
    float Csx;
    
    long flagCsy;
    float Csy;
    
    long flagCsz;
    float Csz;
    
    long Avg;

    long Inv;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageRadialDistributionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageRadialDistributionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageRadialDistributionInfo* info);
extern void init1(mrcImageRadialDistributionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGERADIALDISTRIBUTION_H */
