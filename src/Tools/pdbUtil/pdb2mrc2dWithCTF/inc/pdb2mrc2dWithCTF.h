#ifndef PDB2MRC2DWITHCTF_H
#define PDB2MRC2DWITHCTF_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdb2mrc2dWithCTFInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagNx;
    long Nx;
    
    long flagNy;
    long Ny;
    
    long flagdx;
    float dx;
    
    long flagdy;
    float dy;
    
    long flagcx;
    float cx;
    
    long flagcy;
    float cy;
    
    long flagcz;
    float cz;
    
    long flagnx;
    long nx;
    
    long flagny;
    long ny;
    
    long flagkV;
    float kV;
    
    long flagCs;
    float Cs;
    
    long flagDefocus;
    float Defocus;
    
    long flagAoverP;
    float AoverP;
    
    long flagAin;
    float Ain;
    
    long flagctfMode;
    long ctfMode;
    
    long flagEulerAngle;
    char* EulerAngle;
    
    long flagRot1;
    float Rot1;
    
    long flagRot2;
    float Rot2;
    
    long flagRot3;
    float Rot3;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdb2mrc2dWithCTFInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdb2mrc2dWithCTFInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdb2mrc2dWithCTFInfo* info);
extern void init1(pdb2mrc2dWithCTFInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDB2MRC2DWITHCTF_H */
