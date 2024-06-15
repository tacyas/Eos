#ifndef MRCIMAGEDISPLAYDENSITYASTEMPFACTOR_H
#define MRCIMAGEDISPLAYDENSITYASTEMPFACTOR_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageDisplayDensityAsTempFactorInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagPdb;
    char* Pdb;
    FILE* fptPdb;
    
    long flagValue;
    float Value;
    
    long flagH;
    float H;
    
    long flagL;
    float L;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageDisplayDensityAsTempFactorInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageDisplayDensityAsTempFactorInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageDisplayDensityAsTempFactorInfo* info);
extern void init1(mrcImageDisplayDensityAsTempFactorInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEDISPLAYDENSITYASTEMPFACTOR_H */
