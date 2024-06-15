#ifndef MRCIMAGEVOLUMECALC_H
#define MRCIMAGEVOLUMECALC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageVolumeCalcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagnMolecule;
    float nMolecule;
    
    long flagMolecularWeight;
    float MolecularWeight;
    
    long flagDensity;
    float Density;
    
    long flagDelta;
    float Delta;
    
    long flagMinVol;
    float MinVol;
    
    long flagMaxVol;
    float MaxVol;
    
    long flagDeltaVol;
    float DeltaVol;
    
    long Inverse;

    long flagFormat;
    char* Format;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageVolumeCalcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageVolumeCalcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageVolumeCalcInfo* info);
extern void init1(mrcImageVolumeCalcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEVOLUMECALC_H */
