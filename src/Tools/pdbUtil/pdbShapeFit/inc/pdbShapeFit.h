#ifndef PDBSHAPEFIT_H
#define PDBSHAPEFIT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbShapeFitInfo {
    long flagRedirect;

    long flagInPDB;
    char* InPDB;
    FILE* fptInPDB;
    
    long flagInMRC;
    char* InMRC;
    FILE* fptInMRC;
    
    long flagContour;
    float Contour;
    
    long flagContourMode;
    long ContourMode;
    
    long flagOutMRC;
    char* OutMRC;
    FILE* fptOutMRC;
    
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
    
    long flagsurfaceMode;
    long surfaceMode;
    
    long flagorder;
    float order;
    
    long flagrefine;
    long refine;
    
    long flagsize;
    long size;
    
    long flagweight;
    float weight;
    
    long flagmergin;
    float mergin;
    
    long flagthresHold;
    float thresHold;
    
    long Inverse;

    long Centre;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbShapeFitInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbShapeFitInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbShapeFitInfo* info);
extern void init1(pdbShapeFitInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBSHAPEFIT_H */
