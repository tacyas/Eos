#ifndef MATRIX3DEULERANGLETRANSFORM_H
#define MATRIX3DEULERANGLETRANSFORM_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct matrix3DEulerAngleTransformInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRotationalMode;
    char* RotationalMode;
    
    long flagRotMode;
    char* RotMode;
    
    long flagRot1;
    float Rot1;
    
    long flagRot2;
    float Rot2;
    
    long flagRot3;
    float Rot3;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} matrix3DEulerAngleTransformInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(matrix3DEulerAngleTransformInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(matrix3DEulerAngleTransformInfo* info);
extern void init1(matrix3DEulerAngleTransformInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MATRIX3DEULERANGLETRANSFORM_H */
