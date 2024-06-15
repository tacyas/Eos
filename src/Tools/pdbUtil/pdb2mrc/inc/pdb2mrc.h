#ifndef PDB2MRC_H
#define PDB2MRC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdb2mrcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagnx;
    long nx;
    
    long flagny;
    long ny;
    
    long flagnz;
    long nz;
    
    long flagStartx;
    float Startx;
    
    long flagStarty;
    float Starty;
    
    long flagStartz;
    float Startz;
    
    long flagdx;
    float dx;
    
    long flagdy;
    float dy;
    
    long flagdz;
    float dz;
    
    long flagWeight;
    float Weight;
    
    long flagSigma;
    float Sigma;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdb2mrcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdb2mrcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdb2mrcInfo* info);
extern void init1(pdb2mrcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDB2MRC_H */
