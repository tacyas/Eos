#ifndef MRCIMAGEHELICALMASKINGBY2DIMAGE_H
#define MRCIMAGEHELICALMASKINGBY2DIMAGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageHelicalMaskingBy2DImageInfo {
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
    
    long flagMask;
    char* Mask;
    FILE* fptMask;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageHelicalMaskingBy2DImageInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageHelicalMaskingBy2DImageInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageHelicalMaskingBy2DImageInfo* info);
extern void init1(mrcImageHelicalMaskingBy2DImageInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEHELICALMASKINGBY2DIMAGE_H */
