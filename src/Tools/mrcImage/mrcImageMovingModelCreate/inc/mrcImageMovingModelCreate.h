#ifndef MRCIMAGEMOVINGMODELCREATE_H
#define MRCIMAGEMOVINGMODELCREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageMovingModelCreateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutName;
    char* OutName;
    
    long flagNum;
    long Num;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagNz;
    long Nz;
    
    long flagLx;
    float Lx;
    
    long flagLy;
    float Ly;
    
    long flagLz;
    float Lz;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageMovingModelCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageMovingModelCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageMovingModelCreateInfo* info);
extern void init1(mrcImageMovingModelCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMOVINGMODELCREATE_H */
