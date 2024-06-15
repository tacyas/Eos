#ifndef PDBROTATION_H
#define PDBROTATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbRotationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagZXYrotx;
    float ZXYrotx;
    
    long flagZXYroty;
    float ZXYroty;
    
    long flagZXYrotz;
    float ZXYrotz;
    
    long flagZYXrotx;
    float ZYXrotx;
    
    long flagZYXroty;
    float ZYXroty;
    
    long flagZYXrotz;
    float ZYXrotz;
    
    long flagYXZrotx;
    float YXZrotx;
    
    long flagYXZroty;
    float YXZroty;
    
    long flagYXZrotz;
    float YXZrotz;
    
    long flagXYZrotx;
    float XYZrotx;
    
    long flagXYZroty;
    float XYZroty;
    
    long flagXYZrotz;
    float XYZrotz;
    
    long flagRotMode;
    char* RotMode;
    
    long flagRot1;
    float Rot1;
    
    long flagRot2;
    float Rot2;
    
    long flagRot3;
    float Rot3;
    
    long flagcudaDeviceID;
    long cudaDeviceID;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbRotationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbRotationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbRotationInfo* info);
extern void init1(pdbRotationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBROTATION_H */
