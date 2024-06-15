#ifndef MRCIMAGEGAUSSSPHERE_H
#define MRCIMAGEGAUSSSPHERE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageGaussSphereInfo {
    long flagRedirect;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagEA;
    char* EA;
    
    long flagRot1;
    float Rot1;
    
    long flagRot2;
    float Rot2;
    
    long flagRot3;
    float Rot3;
    
    long flagShiftX;
    float ShiftX;
    
    long flagShiftY;
    float ShiftY;
    
    long flagShiftZ;
    float ShiftZ;
    
    long flagsigmax;
    float sigmax;
    
    long flagsigmay;
    float sigmay;
    
    long flagsigmaz;
    float sigmaz;
    
    long flagsigma_range;
    float sigma_range;
    
    long flagweight;
    float weight;
    
    long flagsize;
    float size;
    
    long flagWidth;
    float Width;
    
    long flagHeight;
    float Height;
    
    long flagSection;
    float Section;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageGaussSphereInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageGaussSphereInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageGaussSphereInfo* info);
extern void init1(mrcImageGaussSphereInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEGAUSSSPHERE_H */
