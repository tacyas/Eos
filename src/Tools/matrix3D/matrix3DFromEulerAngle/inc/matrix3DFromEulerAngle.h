#ifndef MATRIX3DFROMEULERANGLE_H
#define MATRIX3DFROMEULERANGLE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct matrix3DFromEulerAngleInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagEMode;
    char* EMode;
    
    long flagRot1;
    float Rot1;
    
    long flagRot2;
    float Rot2;
    
    long flagRot3;
    float Rot3;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} matrix3DFromEulerAngleInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(matrix3DFromEulerAngleInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(matrix3DFromEulerAngleInfo* info);
extern void init1(matrix3DFromEulerAngleInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MATRIX3DFROMEULERANGLE_H */
