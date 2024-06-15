#ifndef MRCFFTCENTRALSECTIONCOMPARE_H
#define MRCFFTCENTRALSECTIONCOMPARE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcFFTCentralSectionCompareInfo {
    long flagRedirect;

    long flagIn2D;
    char* In2D;
    FILE* fptIn2D;
    
    long flagIn3D;
    char* In3D;
    FILE* fptIn3D;
    
    long flagEAMode;
    char* EAMode;
    
    long flagRot1;
    float Rot1;
    
    long flagRot2;
    float Rot2;
    
    long flagRot3;
    float Rot3;
    
    long flagTransX;
    float TransX;
    
    long flagTransY;
    float TransY;
    
    long flagInterpMode;
    long InterpMode;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcFFTCentralSectionCompareInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcFFTCentralSectionCompareInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcFFTCentralSectionCompareInfo* info);
extern void init1(mrcFFTCentralSectionCompareInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCFFTCENTRALSECTIONCOMPARE_H */
