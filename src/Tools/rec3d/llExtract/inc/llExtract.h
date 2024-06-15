#ifndef LLEXTRACT_H
#define LLEXTRACT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llExtractInfo {
    long flagRedirect;

    long flagTitle;
    char* Title;
    
    long flagxStep;
    float xStep;
    
    long flagyStep;
    float yStep;
    
    long flagMaxX;
    float MaxX;
    
    long flagMaxY;
    float MaxY;
    
    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagNea;
    char* Nea;
    FILE* fptNea;
    
    long flagFar;
    char* Far;
    FILE* fptFar;
    
    long flagRotationAngle;
    float RotationAngle;
    
    long flagOmega;
    float Omega;
    
    long flagShear;
    float Shear;
    
    long flagievery;
    long ievery;
    
    long flagaxl;
    float axl;
    
    long flagayl;
    float ayl;
    
    long flagxShift;
    float xShift;
    
    long flagllMax;
    long llMax;
    
    long flagdelRInv;
    float delRInv;
    
    long flagOutputInfo;

    long flagn;
    long* n;
    
    long flagl;
    long* l;
    
    long flagY;
    float* Y;
    
    long flagleftMin;
    float* leftMin;
    
    long flagleftMax;
    float* leftMax;
    
    long flagrightMin;
    float* rightMin;
    
    long flagrightMax;
    float* rightMax;
    
    long flagweight;
    float* weight;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
} llExtractInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llExtractInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llExtractInfo* info);
extern void init1(llExtractInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLEXTRACT_H */
