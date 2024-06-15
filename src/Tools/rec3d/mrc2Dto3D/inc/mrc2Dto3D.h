#ifndef MRC2DTO3D_H
#define MRC2DTO3D_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrc2Dto3DInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagIn2;
    char** In2;
    char* In2List;
    FILE** fptIn2;
    FILE* fptIn2List;
    
    long each;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut2;
    char* Out2;
    FILE* fptOut2;
    
    long flagRmax;
    float Rmax;
    
    long flagsingle;
    long single;
    
    long flagsingleFilter;
    long singleFilter;
    
    long flagInterpolationMode;
    long InterpolationMode;
    
    long Double;

    long flagDoubleCounter;
    char* DoubleCounter;
    FILE* fptDoubleCounter;
    
    long flagCounterThreshold;
    float CounterThreshold;
    
    long flagCounterThresholdMode;
    long CounterThresholdMode;
    
    long flagWeightMode;
    long WeightMode;
    
    long thicknessWeight;

    long flagSubSampling;
    long SubSampling;
    
    long PlusXrot;

    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagNz;
    long Nz;
    
    long SIRT;

    long flagmaxIter;
    long maxIter;
    
    long flagrms;
    float rms;
    
    long flagCTFInfo;
    char** CTFInfo;
    char* CTFInfoList;
    FILE** fptCTFInfo;
    FILE* fptCTFInfoList;
    
    long flagpthreadMax;
    long pthreadMax;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrc2Dto3DInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrc2Dto3DInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrc2Dto3DInfo* info);
extern void init1(mrc2Dto3DInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRC2DTO3D_H */
