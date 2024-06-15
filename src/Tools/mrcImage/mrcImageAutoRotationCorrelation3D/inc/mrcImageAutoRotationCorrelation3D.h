#ifndef MRCIMAGEAUTOROTATIONCORRELATION3D_H
#define MRCIMAGEAUTOROTATIONCORRELATION3D_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageAutoRotationCorrelation3DInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagCor;
    char* Cor;
    FILE* fptCor;
    
    long flagFit;
    char* Fit;
    FILE* fptFit;
    
    long flagEulerAngle;
    char* EulerAngle;
    
    long flagRot1Min;
    float Rot1Min;
    
    long flagRot1Max;
    float Rot1Max;
    
    long flagRot1Delta;
    float Rot1Delta;
    
    long flagRot2Min;
    float Rot2Min;
    
    long flagRot2Max;
    float Rot2Max;
    
    long flagRot2Delta;
    float Rot2Delta;
    
    long flagRot3Min;
    float Rot3Min;
    
    long flagRot3Max;
    float Rot3Max;
    
    long flagRot3Delta;
    float Rot3Delta;
    
    long flagXrangeMin;
    float XrangeMin;
    
    long flagXrangeMax;
    float XrangeMax;
    
    long flagYrangeMin;
    float YrangeMin;
    
    long flagYrangeMax;
    float YrangeMax;
    
    long flagZrangeMin;
    float ZrangeMin;
    
    long flagZrangeMax;
    float ZrangeMax;
    
    long flagMode;
    long Mode;
    
    long flagModeRotation;
    long ModeRotation;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageAutoRotationCorrelation3DInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageAutoRotationCorrelation3DInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageAutoRotationCorrelation3DInfo* info);
extern void init1(mrcImageAutoRotationCorrelation3DInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEAUTOROTATIONCORRELATION3D_H */
