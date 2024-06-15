#ifndef MRCIMAGEAUTOROTATIONCORRELATIONRESULTPRINT_H
#define MRCIMAGEAUTOROTATIONCORRELATIONRESULTPRINT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageAutoRotationCorrelationResultPrintInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInData;
    char* InData;
    FILE* fptInData;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagPDB;
    char* PDB;
    FILE* fptPDB;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagMax;
    char* Max;
    FILE* fptMax;
    
    long flagMaxRot;
    char* MaxRot;
    FILE* fptMaxRot;
    
    long flagMaxPDB;
    char* MaxPDB;
    FILE* fptMaxPDB;
    
    long flagMaxPDBForRasmol;
    char* MaxPDBForRasmol;
    FILE* fptMaxPDBForRasmol;
    
    long flagSx;
    float Sx;
    
    long flagSy;
    float Sy;
    
    long flagSz;
    float Sz;
    
    long flagTop;
    long Top;
    
    long wish;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageAutoRotationCorrelationResultPrintInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageAutoRotationCorrelationResultPrintInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageAutoRotationCorrelationResultPrintInfo* info);
extern void init1(mrcImageAutoRotationCorrelationResultPrintInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEAUTOROTATIONCORRELATIONRESULTPRINT_H */
