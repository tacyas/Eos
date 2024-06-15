#ifndef MRCIMAGEFILTERCREATE_H
#define MRCIMAGEFILTERCREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageFilterCreateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagNz;
    long Nz;
    
    long flagSx;
    long Sx;
    
    long flagSy;
    long Sy;
    
    long flagSz;
    long Sz;
    
    long verbose;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagMode;
    long Mode;
    
    long flagmode;
    long mode;
    
} mrcImageFilterCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageFilterCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageFilterCreateInfo* info);
extern void init1(mrcImageFilterCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEFILTERCREATE_H */
