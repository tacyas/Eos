#ifndef MATRIX3DTOEULERANGLE_H
#define MATRIX3DTOEULERANGLE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct matrix3DToEulerAngleInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagEulerMode;
    char* EulerMode;
    
    long flagThreshold;
    float Threshold;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} matrix3DToEulerAngleInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(matrix3DToEulerAngleInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(matrix3DToEulerAngleInfo* info);
extern void init1(matrix3DToEulerAngleInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MATRIX3DTOEULERANGLE_H */
