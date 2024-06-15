#ifndef PDB2MRC2D_H
#define PDB2MRC2D_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdb2mrc2dInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut3D;
    char* Out3D;
    FILE* fptOut3D;
    
    long flagdx;
    float dx;
    
    long flagdy;
    float dy;
    
    long flagsx;
    float sx;
    
    long flagsy;
    float sy;
    
    long flagnx;
    long nx;
    
    long flagny;
    long ny;
    
    long flagrotnx;
    long rotnx;
    
    long flagrotny;
    long rotny;
    
    long flagsrotx;
    float srotx;
    
    long flagsroty;
    float sroty;
    
    long flagsrotz;
    float srotz;
    
    long flagsRotMode;
    char* sRotMode;
    
    long flagsRot1;
    float sRot1;
    
    long flagsRot2;
    float sRot2;
    
    long flagsRot3;
    float sRot3;
    
    long flagRotMode;
    char* RotMode;
    
    long flagdRot1;
    float dRot1;
    
    long flagminRot1;
    float minRot1;
    
    long flagmaxRot1;
    float maxRot1;
    
    long flagdRot2;
    float dRot2;
    
    long flagminRot2;
    float minRot2;
    
    long flagmaxRot2;
    float maxRot2;
    
    long flagWeight;
    float Weight;
    
    long flagSigma;
    float Sigma;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagcudaDeviceID;
    long cudaDeviceID;
    
    long flagmode;
    long mode;
    
} pdb2mrc2dInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdb2mrc2dInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdb2mrc2dInfo* info);
extern void init1(pdb2mrc2dInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDB2MRC2D_H */
