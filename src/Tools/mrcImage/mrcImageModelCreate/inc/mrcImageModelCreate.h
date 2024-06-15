#ifndef MRCIMAGEMODELCREATE_H
#define MRCIMAGEMODELCREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageModelCreateInfo {
    long flagRedirect;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagnx;
    long nx;
    
    long flagny;
    long ny;
    
    long flagnz;
    long nz;
    
    long flagr;
    long r;
    
    long flagl;
    long l;
    
    long flaglx;
    float lx;
    
    long flagly;
    float ly;
    
    long flaglz;
    float lz;
    
    long flagradius;
    float radius;
    
    long flagnHelix;
    long nHelix;
    
    long flagzPitch;
    float zPitch;
    
    long flagdeltaPhi;
    float deltaPhi;
    
    long flagphiAngle;
    float phiAngle;
    
    long flagstartZ;
    float startZ;
    
    long flagendZ;
    float endZ;
    
    long flagstartPhi;
    float startPhi;
    
    long flagstartPhi2;
    float startPhi2;
    
    long flaginMode;
    long inMode;
    
    long flagunits;
    long units;
    
    long flagfm;
    long fm;
    
    long flagmin;
    float min;
    
    long flagmax;
    float max;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageModelCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageModelCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageModelCreateInfo* info);
extern void init1(mrcImageModelCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEMODELCREATE_H */
