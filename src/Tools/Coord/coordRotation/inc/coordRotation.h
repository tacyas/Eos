#ifndef COORDROTATION_H
#define COORDROTATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct coordRotationInfo {
    long flagRedirect;

    long flagx;
    float x;
    
    long flagy;
    float y;
    
    long flagz;
    float z;
    
    long flagMat;
    char* Mat;
    FILE* fptMat;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} coordRotationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(coordRotationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(coordRotationInfo* info);
extern void init1(coordRotationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* COORDROTATION_H */
