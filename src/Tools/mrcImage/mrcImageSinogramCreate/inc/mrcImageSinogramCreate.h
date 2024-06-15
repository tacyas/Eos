#ifndef MRCIMAGESINOGRAMCREATE_H
#define MRCIMAGESINOGRAMCREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSinogramCreateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagdphi;
    float dphi;
    
    long flagSmalldphi;
    float Smalldphi;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSinogramCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSinogramCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSinogramCreateInfo* info);
extern void init1(mrcImageSinogramCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESINOGRAMCREATE_H */
