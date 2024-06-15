#ifndef MRCIMAGESUPERRESOLUTION_H
#define MRCIMAGESUPERRESOLUTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSuperResolutionInfo {
    long flagRedirect;

    long flagInOriginal;
    char* InOriginal;
    FILE* fptInOriginal;
    
    long flagInPrevious;
    char* InPrevious;
    FILE* fptInPrevious;
    
    long flagFFTInCount;
    char* FFTInCount;
    FILE* fptFFTInCount;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagt;
    long t;
    
    long flagx00;
    long x00;
    
    long flagy00;
    long y00;
    
    long flagz00;
    long z00;
    
    long flagx01;
    long x01;
    
    long flagy01;
    long y01;
    
    long flagz01;
    long z01;
    
    long flagx10;
    long x10;
    
    long flagy10;
    long y10;
    
    long flagz10;
    long z10;
    
    long flagx11;
    long x11;
    
    long flagy11;
    long y11;
    
    long flagz11;
    long z11;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flaglabelingmode;
    long labelingmode;
    
    long flagmax;
    long max;
    
    long flagmin;
    long min;
    
    long flagshape;
    long shape;
    
    long flaghvp;
    float hvp;
    
    long Inverse;

    long flagnMolecule;
    long nMolecule;
    
    long flagMolecularWeight;
    long MolecularWeight;
    
    long flagDensity;
    float Density;
    
    long flagincounter;
    float incounter;
    
    long flagdeltaDens;
    float deltaDens;
    
    long flagdeltaArea;
    float deltaArea;
    
    long flagsub;
    float sub;
    
    long flagratio;
    float ratio;
    
    long flagtmax;
    long tmax;
    
    long flagWeightDelta;
    float WeightDelta;
    
    long flagWeightMax;
    long WeightMax;
    
    long Subtraction;

} mrcImageSuperResolutionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSuperResolutionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSuperResolutionInfo* info);
extern void init1(mrcImageSuperResolutionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESUPERRESOLUTION_H */
