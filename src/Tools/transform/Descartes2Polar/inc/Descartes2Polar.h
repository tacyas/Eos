#ifndef DESCARTES2POLAR_H
#define DESCARTES2POLAR_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct Descartes2PolarInfo {
    long flagRedirect;

    long flagx;
    float x;
    
    long flagy;
    float y;
    
    long flagz;
    float z;
    
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
    
} Descartes2PolarInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(Descartes2PolarInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(Descartes2PolarInfo* info);
extern void init1(Descartes2PolarInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* DESCARTES2POLAR_H */
