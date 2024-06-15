#ifndef ENERGYTRANSFERMODELCHECK_H
#define ENERGYTRANSFERMODELCHECK_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct energyTransferModelCheckInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagPDB;
    char* PDB;
    FILE* fptPDB;
    
    long flagPDBs;
    char** PDBs;
    char* PDBsList;
    FILE** fptPDBs;
    FILE* fptPDBsList;
    
    long PDBsWithInfo;

    long flagsigma;
    float sigma;
    
    long flagsigmaA;
    float sigmaA;
    
    long flagMRC;
    char* MRC;
    FILE* fptMRC;
    
    long flagMRCs;
    char** MRCs;
    char* MRCsList;
    FILE** fptMRCs;
    FILE* fptMRCsList;
    
    long MRCWithInfo;

    long flagEContour;
    float EContour;
    
    long flagENear;
    float ENear;
    
    long flagENearA;
    float ENearA;
    
    long flagRest;
    char* Rest;
    FILE* fptRest;
    
    long flagRests;
    char** Rests;
    char* RestsList;
    FILE** fptRests;
    FILE* fptRestsList;
    
    long flagContour;
    float Contour;
    
    long flagNear;
    float Near;
    
    long flagNearA;
    float NearA;
    
    long RestrictWithInfo;

    long flagRestP;
    char* RestP;
    FILE* fptRestP;
    
    long flagRestsP;
    char** RestsP;
    char* RestsPList;
    FILE** fptRestsP;
    FILE* fptRestsPList;
    
    long flagSigmaP;
    float SigmaP;
    
    long flagSigmaPA;
    float SigmaPA;
    
    long flagNearP;
    float NearP;
    
    long flagNearPA;
    float NearPA;
    
    long RestrictPW;

    long flagdeltax;
    float deltax;
    
    long flagdeltay;
    float deltay;
    
    long flagdeltaz;
    float deltaz;
    
    long flagsdeltax;
    float sdeltax;
    
    long flagsdeltay;
    float sdeltay;
    
    long flagsdeltaz;
    float sdeltaz;
    
    long flagstartx;
    float startx;
    
    long flagstarty;
    float starty;
    
    long flagstartz;
    float startz;
    
    long flagendx;
    float endx;
    
    long flagendy;
    float endy;
    
    long flagendz;
    float endz;
    
    long flagmaxIter;
    long maxIter;
    
    long flagstartIter;
    long startIter;
    
    long flagneglect;
    float neglect;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} energyTransferModelCheckInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(energyTransferModelCheckInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(energyTransferModelCheckInfo* info);
extern void init1(energyTransferModelCheckInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* ENERGYTRANSFERMODELCHECK_H */
