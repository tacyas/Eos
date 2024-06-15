#ifndef MRCIMAGEHELICALPROJECTION_H
#define MRCIMAGEHELICALPROJECTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageHelicalProjectionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagdz;
    float dz;
    
    long flagdphi;
    float dphi;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageHelicalProjectionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageHelicalProjectionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageHelicalProjectionInfo* info);
extern void init1(mrcImageHelicalProjectionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEHELICALPROJECTION_H */
