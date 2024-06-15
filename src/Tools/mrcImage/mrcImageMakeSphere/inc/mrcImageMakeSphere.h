#ifndef MRCIMAGEMAKESPHERE_H
#define MRCIMAGEMAKESPHERE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageMakeSphereInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagCx;
    float Cx;
    
    long flagCy;
    float Cy;
    
    long flagCz;
    float Cz;
    
    long flagor;
    float or;
    
    long flagir;
    float ir;
    
    long flagr;
    float r;
    
    long flagValue;
    float Value;
    
    long flagOther;
    char* Other;
    FILE* fptOther;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageMakeSphereInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageMakeSphereInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageMakeSphereInfo* info);
extern void init1(mrcImageMakeSphereInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMAKESPHERE_H */
