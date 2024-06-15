#ifndef MRCIMAGESOLVENTFLATTENING_H
#define MRCIMAGESOLVENTFLATTENING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSolventFlatteningInfo {
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
    
    long flagrmax;
    float rmax;
    
    long flagRange;
    float Range;
    
    long flagdensity;
    float density;
    
    long Floating;

    long flagOutParam;
    char* OutParam;
    FILE* fptOutParam;
    
    long flagmode;
    long mode;
    
} mrcImageSolventFlatteningInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSolventFlatteningInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSolventFlatteningInfo* info);
extern void init1(mrcImageSolventFlatteningInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESOLVENTFLATTENING_H */
