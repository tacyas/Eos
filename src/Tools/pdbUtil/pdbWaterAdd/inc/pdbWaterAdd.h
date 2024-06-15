#ifndef PDBWATERADD_H
#define PDBWATERADD_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbWaterAddInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagDensity;
    float Density;
    
    long flagRadius;
    float Radius;
    
    long flagHeight;
    float Height;
    
    long flagX;
    float X;
    
    long flagY;
    float Y;
    
    long flagZ;
    float Z;
    
    long flagEdge;
    long Edge;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbWaterAddInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbWaterAddInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbWaterAddInfo* info);
extern void init1(pdbWaterAddInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBWATERADD_H */
