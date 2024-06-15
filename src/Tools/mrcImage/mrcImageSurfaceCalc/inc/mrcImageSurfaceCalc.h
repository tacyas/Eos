#ifndef MRCIMAGESURFACECALC_H
#define MRCIMAGESURFACECALC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSurfaceCalcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagneighbor;
    long neighbor;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSurfaceCalcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSurfaceCalcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSurfaceCalcInfo* info);
extern void init1(mrcImageSurfaceCalcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESURFACECALC_H */
