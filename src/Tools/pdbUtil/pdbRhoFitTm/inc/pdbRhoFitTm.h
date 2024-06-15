#ifndef PDBRHOFITTM_H
#define PDBRHOFITTM_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbRhoFitTmInfo {
    long flagRedirect;

    long flagInPdb;
    char* InPdb;
    FILE* fptInPdb;
    
    long flagInMrc;
    char* InMrc;
    FILE* fptInMrc;
    
    long flagOutMrc;
    char* OutMrc;
    FILE* fptOutMrc;
    
    long flagSx;
    float Sx;
    
    long flagSy;
    float Sy;
    
    long flagSz;
    float Sz;
    
    long flagOutTxt;
    char* OutTxt;
    FILE* fptOutTxt;
    
    long flagOutPDB;
    char* OutPDB;
    FILE* fptOutPDB;
    
    long flagxmin;
    float xmin;
    
    long flagxmax;
    float xmax;
    
    long flagxDelta;
    float xDelta;
    
    long flagymin;
    float ymin;
    
    long flagymax;
    float ymax;
    
    long flagyDelta;
    float yDelta;
    
    long flagzmin;
    float zmin;
    
    long flagzmax;
    float zmax;
    
    long flagzDelta;
    float zDelta;
    
    long flagEulerAngle;
    char* EulerAngle;
    
    long flagphimin;
    float phimin;
    
    long flagphimax;
    float phimax;
    
    long flagphiDelta;
    float phiDelta;
    
    long flagpsimin;
    float psimin;
    
    long flagpsimax;
    float psimax;
    
    long flagpsiDelta;
    float psiDelta;
    
    long flagthetamin;
    float thetamin;
    
    long flagthetamax;
    float thetamax;
    
    long flagthetaDelta;
    float thetaDelta;
    
    long flagnormalizeWeight;
    float normalizeWeight;
    
    long flagnormalizeContour;
    float normalizeContour;
    
    long Inverse;

    long Zminus;

    long Tfactor;

    long flagTlim;
    float Tlim;
    
    long Centre;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagcontourLevel;
    float* contourLevel;
    
} pdbRhoFitTmInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbRhoFitTmInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbRhoFitTmInfo* info);
extern void init1(pdbRhoFitTmInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBRHOFITTM_H */
