#ifndef MRCIMAGESIEMENSSTAR_H
#define MRCIMAGESIEMENSSTAR_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSiemensStarInfo {
    long flagRedirect;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagR;
    long R;
    
    long flagnRadial;
    long nRadial;
    
    long flagDelta;
    float Delta;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagShape;
    long Shape;
    
    long flagmode;
    long mode;
    
} mrcImageSiemensStarInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSiemensStarInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSiemensStarInfo* info);
extern void init1(mrcImageSiemensStarInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESIEMENSSTAR_H */
