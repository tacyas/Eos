#ifndef PDBTWOPROTEINFIT_H
#define PDBTWOPROTEINFIT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbTwoProteinFitInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInResidue;
    char* InResidue;
    FILE* fptInResidue;
    
    long flagSelectIn;
    char* SelectIn;
    FILE* fptSelectIn;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagRefResidue;
    char* RefResidue;
    FILE* fptRefResidue;
    
    long flagSelectRef;
    char* SelectRef;
    FILE* fptSelectRef;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagMatrix;
    char* Matrix;
    FILE* fptMatrix;
    
    long flagParam;
    char* Param;
    FILE* fptParam;
    
    long flagoutDis;
    char* outDis;
    FILE* fptoutDis;
    
    long flagoutDis2;
    char* outDis2;
    FILE* fptoutDis2;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbTwoProteinFitInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbTwoProteinFitInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbTwoProteinFitInfo* info);
extern void init1(pdbTwoProteinFitInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBTWOPROTEINFIT_H */
