#ifndef PDBCHARGEFIT_H
#define PDBCHARGEFIT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbChargeFitInfo {
    long flagRedirect;

    long flagInFix;
    char* InFix;
    FILE* fptInFix;
    
    long flagInMove;
    char* InMove;
    FILE* fptInMove;
    
    long flagOutTxt;
    char* OutTxt;
    FILE* fptOutTxt;
    
    long flagsymmetry;
    float symmetry;
    
    long flagzmin;
    float zmin;
    
    long flagzmax;
    float zmax;
    
    long flagzDel;
    float zDel;
    
    long flagmind;
    float mind;
    
    long flagmaxd;
    float maxd;
    
    long flagaxisX;
    float axisX;
    
    long flagaxisY;
    float axisY;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbChargeFitInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbChargeFitInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbChargeFitInfo* info);
extern void init1(pdbChargeFitInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBCHARGEFIT_H */
