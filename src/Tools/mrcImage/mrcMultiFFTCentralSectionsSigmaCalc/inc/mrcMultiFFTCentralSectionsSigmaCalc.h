#ifndef MRCMULTIFFTCENTRALSECTIONSSIGMACALC_H
#define MRCMULTIFFTCENTRALSECTIONSSIGMACALC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcMultiFFTCentralSectionsSigmaCalcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagPathIn;
    char* PathIn;
    
    long flagInLikelihood;
    char** InLikelihood;
    char* InLikelihoodList;
    FILE** fptInLikelihood;
    FILE* fptInLikelihoodList;
    
    long flagPathL;
    char* PathL;
    
    long flagIn3D;
    char** In3D;
    char* In3DList;
    FILE** fptIn3D;
    FILE* fptIn3DList;
    
    long flagPath3D;
    char* Path3D;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagEulerMode;
    char* EulerMode;
    
    long flagRot1Start;
    float Rot1Start;
    
    long flagRot1End;
    float Rot1End;
    
    long flagRot1Delta;
    float Rot1Delta;
    
    long flagRot2Start;
    float Rot2Start;
    
    long flagRot2End;
    float Rot2End;
    
    long flagRot2Delta;
    float Rot2Delta;
    
    long flagRot3Start;
    float Rot3Start;
    
    long flagRot3End;
    float Rot3End;
    
    long flagRot3Delta;
    float Rot3Delta;
    
    long flagTransX;
    float TransX;
    
    long flagTransY;
    float TransY;
    
    long flagInterpMode;
    long InterpMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcMultiFFTCentralSectionsSigmaCalcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcMultiFFTCentralSectionsSigmaCalcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcMultiFFTCentralSectionsSigmaCalcInfo* info);
extern void init1(mrcMultiFFTCentralSectionsSigmaCalcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCMULTIFFTCENTRALSECTIONSSIGMACALC_H */
