#ifndef MRCMULTIFFTCENTRALSECTIONSCOMPARE_H
#define MRCMULTIFFTCENTRALSECTIONSCOMPARE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcMultiFFTCentralSectionsCompareInfo {
    long flagRedirect;

    long flagIn2D;
    char* In2D;
    FILE* fptIn2D;
    
    long flagIn3D;
    char* In3D;
    FILE* fptIn3D;
    
    long flagvolPath;
    char* volPath;
    
    long flagPrior;
    char* Prior;
    FILE* fptPrior;
    
    long flagPriPath;
    char* PriPath;
    
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
    
    long flagOut1;
    char* Out1;
    FILE* fptOut1;
    
    long flagOutLikelihood;
    char* OutLikelihood;
    FILE* fptOutLikelihood;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagLcalcmode;
    long Lcalcmode;
    
    long flagLmode1;
    float Lmode1;
    
    long flagLmode2;
    float Lmode2;
    
    long flagmode;
    long mode;
    
} mrcMultiFFTCentralSectionsCompareInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcMultiFFTCentralSectionsCompareInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcMultiFFTCentralSectionsCompareInfo* info);
extern void init1(mrcMultiFFTCentralSectionsCompareInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCMULTIFFTCENTRALSECTIONSCOMPARE_H */
