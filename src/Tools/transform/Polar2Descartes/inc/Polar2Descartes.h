#ifndef POLAR2DESCARTES_H
#define POLAR2DESCARTES_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct Polar2DescartesInfo {
    long flagRedirect;

    long flagr;
    float r;
    
    long flagphi;
    float phi;
    
    long flagtheta;
    float theta;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagcx;
    float cx;
    
    long flagcy;
    float cy;
    
    long flagcz;
    float cz;
    
    long flagxx;
    float xx;
    
    long flagxy;
    float xy;
    
    long flagxz;
    float xz;
    
    long flagzx;
    float zx;
    
    long flagzy;
    float zy;
    
    long flagzz;
    float zz;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} Polar2DescartesInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(Polar2DescartesInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(Polar2DescartesInfo* info);
extern void init1(Polar2DescartesInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* POLAR2DESCARTES_H */
