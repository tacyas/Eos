#ifndef MRCIMAGEHELICALMASKING_H
#define MRCIMAGEHELICALMASKING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageHelicalMaskingInfo {
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
    
    long flagdz;
    float dz;
    
    long flagdphi;
    float dphi;
    
    long flagsz;
    long sz;
    
    long flagez;
    long ez;
    
    long flagsphi;
    float sphi;
    
    long flagephi;
    float ephi;
    
    long flagvalue;
    float value;
    
    long flagmode;
    long mode;
    
} mrcImageHelicalMaskingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageHelicalMaskingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageHelicalMaskingInfo* info);
extern void init1(mrcImageHelicalMaskingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEHELICALMASKING_H */
